package imports;

public class Superclass {
	private static String block_1 = printBlock("(1) parent static init block 1");
	private String block_6 = printBlock("(6) parent init block 1");
	static { // dk how this works though
		printBlock("(2) parent static init block 2");
	}
	{ // neither this one
		printBlock("(7) parent init block 2");
	}

	public Superclass(String something) {
		printBlock("(8) parent param constructor");
	}

	public static String printBlock(String text) {
		System.out.println(text);
		return text;
	}
}
