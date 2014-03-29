#include "IMGLoad.h"

#include <jni.h>
#include <png.h>
#include <jpeglib.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#ifndef PNG_SETJMP_NOT_SUPPORTED
#include <setjmp.h>
#endif

#define FILE_TYPE_INVALID 0
#define FILE_TYPE_PNG 1
#define FILE_TYPE_JPG 2

unsigned char jpg_magic[] = { 0xff, 0xd8 };
size_t jpg_magic_length = 2;
unsigned char png_magic[] = { 0x89, 0x50, 0x4e, 0x47, 0x0d, 0x0a, 0x1a, 0x0a };
size_t png_magic_length = 8;

int get_file_type(FILE* fp);
jobject load_png(JNIEnv* env, FILE* fp, const char* filename);
jobject load_jpg(JNIEnv* env, FILE* fp, const char* filename);

JNIEXPORT jobject JNICALL Java_IMGLoad_loadImage(JNIEnv* env, jclass c, jstring filename) {
  jobject ret = 0;
  const char* native_filename = (*env)->GetStringUTFChars(env, filename, 0);
  FILE* fp = fopen(native_filename, "rb");
  if(!fp) {
    fprintf(stderr, "Could not open file %s\n", native_filename);
    goto cleanup_minimal;
  }
  int file_type = get_file_type(fp);
  switch(file_type) {
  case FILE_TYPE_PNG:
    ret = load_png(env, fp, native_filename);
    break;
  case FILE_TYPE_JPG:
    ret = load_jpg(env, fp, native_filename);
    break;
  default:
    fprintf(stderr, "Unrecognized file type for %s\n", native_filename);
    break;
  }
  fclose(fp);
 cleanup_minimal:
  (*env)->ReleaseStringUTFChars(env, filename, native_filename);
  return ret;
}

int get_file_type(FILE* fp) {
  unsigned char buffer[8];
  size_t bytes_read = fread(buffer, 1, 8, fp);
  fprintf(stderr, "File magic: %x:%x:%x:%x:%x:%x:%x:%x\n",
	  buffer[0],
	  buffer[1],
	  buffer[2],
	  buffer[3],
	  buffer[4],
	  buffer[5],
	  buffer[6],
	  buffer[7]);
  fseek(fp, 0L, SEEK_SET);
  if(bytes_read >= png_magic_length && memcmp(buffer, png_magic, png_magic_length) == 0) {
    return FILE_TYPE_PNG;
  } else if(bytes_read >= jpg_magic_length && memcmp(buffer, jpg_magic, jpg_magic_length) == 0) {
    return FILE_TYPE_JPG;
  }
  return FILE_TYPE_INVALID;
}

jobject load_png(JNIEnv* env, FILE* fp, const char* filename) {
  unsigned char header[8];

  fread(header, 1, 8, fp);
  if(!!png_sig_cmp(header, 0, 8)) {
    //This should never happen because of the check in get_file_type.
    fprintf(stderr, "%s is not a valid PNG file\n", filename);
    fclose(fp);
    return 0;
  }

  png_structp png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);

  if(!png_ptr) {
    fprintf(stderr, "Failed to create PNG read struct!\n");
    fclose(fp);
    return 0;
  }

  png_infop info_ptr = png_create_info_struct(png_ptr);
  if(!info_ptr) {
    fprintf(stderr, "Failed to create PNG info struct!\n");
    png_destroy_read_struct(&png_ptr, NULL, NULL);
    fclose(fp);
    return 0;
  }

  png_infop end_ptr = png_create_info_struct(png_ptr);
  if(!end_ptr) {
    fprintf(stderr, "Failed to create PNG end struct!\n");
    png_destroy_read_struct(&png_ptr, &info_ptr, NULL);
    fclose(fp);
    return 0;
  }

  png_init_io(png_ptr, fp);
  png_set_sig_bytes(png_ptr, 8);

#ifndef PNG_SETJMP_NOT_SUPPORTED
  if(setjmp(png_jmpbuf(png_ptr))) {
    fprintf(stderr, "Error reading %s\n", filename);
    png_destroy_read_struct(&png_ptr, &info_ptr, &end_ptr);
    fclose(fp);
    return 0;
  }
#endif

  png_read_info(png_ptr, info_ptr);

  //int width = png_get_image_width(png_ptr, info_ptr);
  int height = png_get_image_height(png_ptr, info_ptr);

  png_byte color_type = png_get_color_type(png_ptr, info_ptr);
  png_byte bit_depth = png_get_bit_depth(png_ptr, info_ptr);

  if(color_type != PNG_COLOR_TYPE_RGB && color_type != PNG_COLOR_TYPE_RGB_ALPHA) {
    fprintf(stderr, "Unsupported color type %x\n", color_type);
    png_destroy_read_struct(&png_ptr, &info_ptr, &end_ptr);
    fclose(fp);
    return 0;
  }

  if(bit_depth != 8) {
    fprintf(stderr, "Unsupported bit depth %x\n", bit_depth);
    png_destroy_read_struct(&png_ptr, &info_ptr, &end_ptr);
    fclose(fp);
    return 0;
  }

  png_bytep* row_pointers = png_malloc(png_ptr, sizeof(png_bytep) * height);
  size_t rowbytes = png_get_rowbytes(png_ptr, info_ptr);
  int y;
  for(y = 0; y < height; y++) {
    row_pointers[y] = png_malloc(png_ptr, rowbytes);
  }

  png_read_image(png_ptr, row_pointers);
  png_read_end(png_ptr, end_ptr);

  jclass cls = (*env)->FindClass(env, "java/nio/ByteBuffer");
  jmethodID aloc = (*env)->GetStaticMethodID(env, cls, "allocateDirect", "(I)Ljava/nio/ByteBuffer;");
  jobject bb = (*env)->CallStaticObjectMethod(env, cls, aloc, height * rowbytes);

  unsigned char* bb_data = (*env)->GetDirectBufferAddress(env, bb);
  for(y = 0; y < height; y++) {
    memcpy(bb_data + y, row_pointers[y], rowbytes);
  }

  for(y = 0; y < height; y++) {
    png_free(png_ptr, row_pointers[y]);
  }
  png_free(png_ptr, row_pointers);
  png_destroy_read_struct(&png_ptr, &info_ptr, &end_ptr);

  return bb;
}

jobject load_jpg(JNIEnv* env, FILE* fp, const char* filename) {
  struct jpeg_decompress_struct cinfo;
  struct jpeg_error_mgr jerr;
  //JSAMPROW row_pointer[1];

  cinfo.err = jpeg_std_error(&jerr);
  jpeg_create_decompress(&cinfo);
  jpeg_stdio_src(&cinfo, fp);
  jpeg_read_header(&cinfo, 1);
  jpeg_start_decompress(&cinfo);

  jclass cls = (*env)->FindClass(env, "java/nio/ByteBuffer");
  jmethodID aloc = (*env)->GetStaticMethodID(env, cls, "allocateDirect", "(I)Ljava/nio/ByteBuffer;");
  jobject bb = (*env)->CallStaticObjectMethod(env, cls, aloc,
					      cinfo.output_width *
					      cinfo.output_height *
					      cinfo.num_components);

  unsigned char* bb_data = (*env)->GetDirectBufferAddress(env, bb);
  unsigned char* bb_ptr = bb_data;
  size_t row_length = cinfo.image_width * cinfo.num_components;
  while(cinfo.output_scanline < cinfo.image_height) {
    jpeg_read_scanlines(&cinfo, &bb_ptr, 1);
    //memcpy(bb_ptr, row_pointer, cinfo.image_width * cinfo.num_components);
    bb_ptr += row_length;
  }

  jpeg_finish_decompress(&cinfo);
  jpeg_destroy_decompress(&cinfo);

  return bb;
}
