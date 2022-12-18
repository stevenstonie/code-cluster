package imports;

public class Class extends Superclass {
	private static String block_3 = printBlock("(3) child static init block 1");
	private String block_9 = printBlock("(9) child init block 1");
	static {
		printBlock("(4) child static init block 2");
	}

	public Class(String something) {
		super(printBlock(something)); // has to be first line. inserting something above will give an error
		printBlock("(10) child param constructor");
	}
}
