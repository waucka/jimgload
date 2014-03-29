import org.impulse101.libimgload.IMGLoad;
import org.impulse101.libimgload.Image;
import java.nio.ByteBuffer;

public class TestIMGLoad {
    public static void main(String[] args) {
	{
	    System.out.print("Loading image: ");
	    System.out.println(args[0]);
	    Image img = IMGLoad.loadImage(args[0]);
	    if(img == null) {
		System.exit(1);
	    }
	    ByteBuffer bb = img.getBytes();
	    if(bb == null) {
		System.err.println("No data!");
		System.exit(1);
	    }
	    if(img.getWidth() != 1920 || img.getHeight() != 1200) {
		System.err.println("Bad size: " + img.getWidth() + "x" + img.getHeight());
		System.exit(1);
	    }
	    if(img.getBPP() != 24) {
		System.err.println("Bad BPP: " + img.getBPP());
		System.exit(1);
	    }
	    if(bb != null) {
		System.out.println("size: " + bb.capacity());
	    } else {
		System.out.println("FAIL!");
		System.exit(1);
	    }
	}
	{
	    System.out.print("Loading image: ");
	    System.out.println(args[1]);
	    Image img = IMGLoad.loadImage(args[1]);
	    if(img == null) {
		System.exit(1);
	    }
	    ByteBuffer bb = img.getBytes();
	    if(bb == null) {
		System.err.println("No data!");
		System.exit(1);
	    }
	    if(img.getWidth() != 3866 || img.getHeight() != 2426) {
		System.err.println("Bad size: " + img.getWidth() + "x" + img.getHeight());
		System.exit(1);
	    }
	    if(img.getBPP() != 24) {
		System.err.println("Bad BPP: " + img.getBPP());
		System.exit(1);
	    }
	    if(bb != null) {
		System.out.println("size: " + bb.capacity());
	    } else {
		System.out.println("FAIL!");
		System.exit(1);
	    }
	}
	{
	    System.out.print("Loading image: ");
	    System.out.println(args[2]);
	    Image img = IMGLoad.loadImage(args[2]);
	    if(img == null) {
		System.exit(1);
	    }
	    ByteBuffer bb = img.getBytes();
	    if(bb == null) {
		System.err.println("No data!");
		System.exit(1);
	    }
	    if(img.getWidth() != 32 || img.getHeight() != 32) {
		System.err.println("Bad size: " + img.getWidth() + "x" + img.getHeight());
		System.exit(1);
	    }
	    if(img.getBPP() != 32) {
		System.err.println("Bad BPP: " + img.getBPP());
		System.exit(1);
	    }
	    if(bb != null) {
		System.out.println("size: " + bb.capacity());
	    } else {
		System.out.println("FAIL!");
		System.exit(1);
	    }
	}
    }
}
