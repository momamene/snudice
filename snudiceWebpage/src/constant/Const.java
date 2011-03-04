package constant;

public class Const {
	public static String root = "/snudiceWebpage"; //root 경로
	
	public static int sessionTimeout = 1800; //세션 만료 시간(초)
	
	public static int articlePerPage = 10; //게시판 한 페이지당 보여줄 글 수
	public static int pageNumberPerPage = 6; //게시판 한 페이지당 보여줄 페이지번호 수	
	public static int artilcePerPageMain = 6; //첫 화면에서 보여줄 각 게시판의 글 수
	public static int userIdMaxLen = 12; //userId의 최대길이	
	public static int emailMaxLen = 80; //email의 최대 길이
	public static int nicknameMaxLen = 12; //nickname 최대길이(byte 수)
	public static int commentMaxLen = 20; //자기소개의 최대 길이(byte 수)
	public static int newPwDigits = 8; //패스워드 리셋시 newPwDigits 자리수만큼의 10진수로 리셋됨
	
	public static int articleTitleMaxLen = 50; //글 제목 최대길이
	public static int articleTextMaxLen = 5000; //글 내용 최대길이
	
	public static int articleTitleInListMaxLen = 15; //글 목록보기에서의 글 제목 최대 길이
}
