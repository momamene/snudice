package ElementPackage;

import org.omg.Dynamic.Parameter;

// 일단은 x,y,z로만 구성, n차원으로의 확장에 대해서는 아직 고려하지 않음. -> DataVector 랑 합칠것
public class SpaceVector extends Vector{
	public SpaceVector()	{
		super(ConstForSVM.SPACEDIMENSION);
		this.setX(0.0f);
		this.setY(0.0f);
		this.setZ(0.0f);
	}
	public SpaceVector(double x, double y, double z)	{
		super(ConstForSVM.SPACEDIMENSION);
		this.setX(x);
		this.setY(y);
		this.setZ(z);
	}
	public void setX(double x) {
		setParameter(0,x);
	}
	public double getX() {
		return 	getParameter(0);
	}
	public void setZ(double z) {
		setParameter(2,z);
	}
	public double getZ() {
		return 	getParameter(2);
	}
	public void setY(double y) {
		parameter[1] = y;
	}
	public double getY() {
		return getParameter(1);
	}
}
