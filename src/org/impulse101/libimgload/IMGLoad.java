package org.impulse101.libimgload;

import java.nio.ByteBuffer;

public class IMGLoad {
    public static native ByteBuffer loadImage(String filename);

    static {
	System.loadLibrary("imgload");
    }
}
