package utility;

import java.security.MessageDigest;
import java.security.NoSuchAlgorithmException;

public class Encrypt {
	public static String encrypt(String str) {
		return(md5(md5(str)));
	}	
	
	private static String md5(String str) {
		MessageDigest md = null;
		try
		{
			md = MessageDigest.getInstance("MD5");
		}
		catch(NoSuchAlgorithmException e)
		{
			e.printStackTrace();
		}
		
		md.update(str.getBytes());
		byte[] md5Code = md.digest();
		StringBuffer sb = new StringBuffer();
		for(int i=0;i<md5Code.length;i++)
		{
			String md5Char = String.format("%02x", 0xff&(char)md5Code[i]);
			sb.append(md5Char);
		}
		
		return sb.toString();
	}
}
