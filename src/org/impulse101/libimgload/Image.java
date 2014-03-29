package org.impulse101.libimgload;

import java.nio.ByteBuffer;

public class Image {
    private ByteBuffer _buf;
    private int _width;
    private int _height;
    private int _bpp;

    public Image(ByteBuffer buf, int width, int height, int bpp) {
	_buf = buf;
	_width = width;
	_height = height;
	_bpp = bpp;
    }

    public ByteBuffer getBytes() {
	return _buf;
    }

    public int getWidth() {
	return _width;
    }

    public int getHeight() {
	return _height;
    }

    public int getBPP() {
	return _bpp;
    }
}
