package constant;

public class Const {
	public static String root = "/snudiceWebpage"; //root 경로
	public static int articlePerPage = 10; //게시판 한 페이지당 보여줄 글 수
	public static int pageNumberPerPage = 6; //게시판 한 페이지당 보여줄 페이지번호 수	
	public static int artilcePerPageMain = 5; //첫 화면에서 보여줄 각 게시판의 글 수
	public static String validIdRegex = "([a-z]|[0-9])+"; //올바른 id를 나타내는 정규식
	public static int userIdMaxLen = 16; //userId의 최대길이
	public static int passwordMaxLen = 80; //password의 최대길이
	public static int emailMaxLen = 80; //email의 최대 길이
	
	public static int articleTitleMaxLen = 50; //글 제목 최대길이
	public static int articleTextMaxLen = 5000; //글 내용 최대길이
}
