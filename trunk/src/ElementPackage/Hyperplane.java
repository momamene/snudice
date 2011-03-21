package ElementPackage;

public class Hyperplane {
	private Vector gradiant ;
	private double bias ;
	public Hyperplane()	{
		
	}
	public void setGradiant(Vector gradiant) {
		this.gradiant = gradiant;
	}
	public Vector getGradiant() {
		return gradiant;
	}
	public void setBias(double bias) {
		this.bias = bias;
	}
	public double getBias() {
		return bias;
	}
}
