package classes.auxiliaryclasses;

import com.stevensproject.App;

public class Inutils {
	public static short getSmallIntInputFromUser() {
		String s_userInput = App.console.nextLine();

		for (int i = 0; i < s_userInput.length(); i++)
			if (!Character.isDigit(s_userInput.charAt(i)))
				return -1;

		int i_userInput = Integer.parseInt(s_userInput);
		if (i_userInput > Short.MAX_VALUE || i_userInput < Short.MIN_VALUE)
			return -1;

		return (short) i_userInput;
	}
}
