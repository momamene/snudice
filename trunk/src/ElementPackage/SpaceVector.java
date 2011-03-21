package ElementPackage;

import org.omg.Dynamic.Parameter;

// �ϴ��� x,y,z�θ� ����, n���������� Ȯ�忡 ���ؼ��� ���� ������� ����. -> DataVector �� ��ĥ��
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
