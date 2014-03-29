package org.impulse101.libimgload;

import java.nio.ByteBuffer;

public class Image {
    private ByteBuffer _buf;
    private int _width;
    private int _height;

    public Image(ByteBuffer buf, int width, int height) {
	_buf = buf;
	_width = width;
	_height = height;
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
}
