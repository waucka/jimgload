package org.impulse101.jimgload;

public class IMGLoad {
    public static native Image loadImage(String filename);

    static {
	System.loadLibrary("imgload");
    }
}
