import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.StandardOpenOption;

public class incrementAsPalindromes {
	public static long mirror(long half_palindrome, boolean includeUnitsDig){
		// go from either the last or penultimate digit to the first one and mirror the number on the right. (include the last digit if param == true)
		String full_palindrome = Long.toString(half_palindrome);
		int i;
		// cannot do arithmetic operations with boolean as -boolean /:
		if(includeUnitsDig == true) i = full_palindrome.length() - 1;
		else i = full_palindrome.length() - 2;

		while(i>=0){
			full_palindrome += full_palindrome.charAt(i);
			--i;
		}

		return Long.parseLong(full_palindrome);
	}

	public static void main(String... args){
		long half_palindrome = 0, full_palindrome = 0;
		boolean includeUnitsDig = false;
		long lastLength = Long.toString(half_palindrome).length();
		// 'lastLength' and 'includeUnitsDig' check if a number (for ex) 10 should be mirrored as either 101 or 1001, 123 as either 12321 or 123321, etc.
		// ==> we do TWO mirrors on the same length of numbers => per each ``longer`` length we delete the last digit ONCE so that 
		// one time we include the units digit in the mirroring and the second time we dont.

		try{
			Path filePath = Path.of("./palindromes.txt");
			Files.writeString(filePath, "");	// delete file contents after opening it
			
			for(; full_palindrome < 1000000L;){
				if(Long.toString(half_palindrome).length() > lastLength){
					if(includeUnitsDig == false){
						includeUnitsDig = true;
						half_palindrome /= 10;
					}
					else if(includeUnitsDig == true){
						includeUnitsDig = false;
						lastLength = Long.toString(half_palindrome).length();
					}
				}
				full_palindrome = mirror(half_palindrome, includeUnitsDig);
				
				Files.writeString(filePath, Long.toString(full_palindrome) + "\n", StandardOpenOption.APPEND);
				half_palindrome++;
			}
		}catch(IOException e){
			e.printStackTrace();
		}
	}
}
