package utility;

import java.security.Security;
import java.util.Properties;

import javax.mail.Message;
import javax.mail.MessagingException;
import javax.mail.PasswordAuthentication;
import javax.mail.Session;
import javax.mail.Transport;
import javax.mail.internet.InternetAddress;
import javax.mail.internet.MimeMessage;

public class GmailSend {
	/////////////////////////////////////////////////////////////
	private static final boolean debug = false;
	private static final String SMTP_AUTH_USER = "snudice@gmail.com";
	private static final String SMTP_AUTH_PWD = "snudice_web_12468";	
	/////////////////////////////////////////////////////////////
	
	private static final String SMTP_HOST_NAME = "smtp.gmail.com";
	private static final String SMTP_PORT = "465";	
	private static final String SSL_FACTORY = "javax.net.ssl.SSLSocketFactory";	
	
	//singleton
	private volatile static GmailSend instance;	
	public static GmailSend getInstance() {
		if(instance==null)
		{
			synchronized (GmailSend.class) {
				if(instance==null)
					instance = new GmailSend();
			}
		}
		
		return instance;
	}
	
	private GmailSend() {
		Security.addProvider(new com.sun.net.ssl.internal.ssl.Provider());
	}
	
	//메일을 발송함
	public void sendSSLMessage(String recipients[], String subject,String message, String from) throws MessagingException {	
		Properties props = new Properties();
		props.put("mail.smtp.host", SMTP_HOST_NAME);
		props.put("mail.smtp.auth", "true");
		if(debug)
			props.put("mail.debug", "true");
		else
			props.put("mail.debug", "false");
		props.put("mail.smtp.port", SMTP_PORT);
		props.put("mail.smtp.socketFactory.port", SMTP_PORT);
		props.put("mail.smtp.socketFactory.class", SSL_FACTORY);
		props.put("mail.smtp.socketFactory.fallback", "false");
	
		Session session = Session.getDefaultInstance(props,	new SMTPAuthenticator());
	
		session.setDebug(debug);
		
		Message msg = new MimeMessage(session);
		InternetAddress addressFrom = new InternetAddress(from);
		msg.setFrom(addressFrom);
		
		InternetAddress[] addressTo = new InternetAddress[recipients.length];
		for (int i = 0; i < recipients.length; i++) 	
			addressTo[i] = new InternetAddress(recipients[i]);
		
		msg.setRecipients(Message.RecipientType.TO, addressTo);
		
		// Setting the Subject and Content Type
		msg.setSubject(subject);
		msg.setContent(message, "text/plain; charset=UTF-8");
		Transport.send(msg);		
	}
	
	private class SMTPAuthenticator extends javax.mail.Authenticator
	{
	    public PasswordAuthentication getPasswordAuthentication()
	    {
	        String username = SMTP_AUTH_USER;
	        String password = SMTP_AUTH_PWD;
	        return new PasswordAuthentication(username, password);
	    }
	}
}

