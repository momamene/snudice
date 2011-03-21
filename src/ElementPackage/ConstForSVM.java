package ElementPackage;

public class ConstForSVM {
	public final static double AccelPermittedLimit = 3.0f;
	public final static int MAXFRAME = 3;
	public final static int SPACEDIMENSION = 3;
	public static int getVectorSize()	{
		return SPACEDIMENSION * MAXFRAME;
	}
}
