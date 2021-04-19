package homeworks;

import static org.junit.jupiter.api.Assertions.*;

import java.io.IOException;

import org.junit.jupiter.api.Test;

class AnagramsTest {

	@Test
	void testBuildLetterTable() {//all letters are correctly assigned
		Anagrams a = new Anagrams();
		assertEquals(a.letterTable.toString(), 
				"{a=2, b=3, c=5, d=7, e=11, f=13, g=17, h=19, i=23, j=29, "
				+ "k=31, l=37, m=41, n=43, o=47, p=53, q=59, r=61, s=67, "
				+ "t=71, u=73, v=79, w=83, x=89, y=97, z=101}");
	}

	@Test
	void testAddWord() {//has the hash/word been added
		Anagrams a = new Anagrams();
		a.addWord("testing");
		//System.out.println(a.anagramTable);
		assertEquals(a.anagramTable.toString(), "{62463943421=[testing]}");
	}

	@Test
	void testMyHashCode() {
		Anagrams a = new Anagrams();
		assertEquals(a.myHashCode("a"), 2L); // a=2
		assertEquals(a.myHashCode("abcde"), 2310L); // a=2 * b=3 * c=5 * d=7 * e=11 = 2310
		
	}

	@Test
	void testGetMaxEntries() {
		Anagrams a = new Anagrams();
		try {
			a.processFile("words_alpha.txt");
		} catch (IOException e1) {
			e1.printStackTrace();
		}
		assertEquals(a.getMaxEntries().toString(), "[236204078=[alerts, alters, artels, estral, laster, lastre, rastle, ratels, relast, resalt, salter, slater, staler, stelar, talers]]");
	}
}