package src.main.java.com;

import imports.Class;

// https://stackoverflow.com/a/50966284/18588243
public class Main {
	public static void main(String[] args) {
		System.out.println("init");
		Class example = new Class("(5) super block of param constructor");
		Class.printBlock("(11) manually called static function");
		// - (init blocks are executed before constructors
		// at the time of class initialization!!)
		// - however because it is a child class its default constructor is called first
		// instead of the static init blocks
		// - when its default constructor is executed, it goes into the default
		// constructor of the parent class, hence loading it
		// ==> init static blocks of ```parent``` class. (1) (2)
		// - after the default constructor of the child class,
		// its init static blocks are being called (3) (4)
		// - the parametized constructor in child class is being called, goes through
		// 'super(stage())' and executes the function in the parent class which
		// prints the parameter given (5)
		// - init blocks of super class are executed (6) and (7)
		// - parametized constructor in parent class is executed (8)
		// - init block of child class is executed (9)
		// - parametized constructor in child class is executed (10)
		// - static method called manually (11)

		// --> static init blocks of the oldest class to the newest
		// --> super blocks
		// --> init blocks AND constructor of oldest class to the newest
		// --> manually called methods

	} // - imagine the destructor is called after this line
}
