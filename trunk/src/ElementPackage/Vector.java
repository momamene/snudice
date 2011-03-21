package ElementPackage;

public class Vector {
	protected double[] parameter;
	private int size;
	
	public Vector(int size)	{
		setSize(size);
		parameter = new double[size];
	}
	
	public void setParameter(int index , double value ) {
		this.parameter[index] = value;
	}
	public double getParameter(int index) {
		return parameter[index];
	}
	public void setParameter(double[] parameter) {
		this.parameter = parameter;
	}
	public double[] getParameter() {
		return parameter;
	}
	public void setSize(int size) {
		this.size = size;
	}
	public int getSize() {
		return size;
	}
	
	public void print()
	{
		
		System.out.println("dataVector : ");
		for (int j=0;j<size;j++)
			System.out.println(this.getParameter(j) + ",");
		System.out.println("------------------------------------");

	}
	public double distance(Vector target)	{
		double retVal = 0.0f;
		double sum = 0.0f;
		for (int i = 0 ; i < size ; i++ )	{
			sum += (getParameter(i) - target.getParameter(i))
					*(getParameter(i) - target.getParameter(i));
		}
		retVal = Math.sqrt(sum);
		return retVal;
	}
	
	public Vector getDeltaVector(Vector target)	{
		if (this.getSize() != target.getSize())	{
			throw new RuntimeException("It is not permitted to get deltaVector with difference frame");
		}
		Vector retVec = new Vector(size);
		double vecLength = 0.0f;
		for (int i = 0 ; i < size ; i++ )	{
			retVec.setParameter (i ,  (getParameter(i) - target.getParameter(i)) );
			vecLength += retVec.getParameter(i)*retVec.getParameter(i);
		}
		vecLength = Math.sqrt(vecLength);
		for (int i = 0 ; i < size ; i++ )	{
			retVec.setParameter (i , retVec.getParameter(i)/vecLength );
		}
		return retVec;
	}
	
	public double getProduct(Vector target)	{
		if (this.getSize() != target.getSize())	{
			throw new RuntimeException("It is not permitted to get deltaVector with difference frame");
		}
		double retVal = 0.0f;
		
		for (int i = 0 ; i < size ; i++ )	{
			retVal += getParameter(i) * target.getParameter(i);
		}
		
		return retVal;
	}
	public Vector getPlus(Vector target)	{
		if (this.getSize() != target.getSize())	{
			throw new RuntimeException("It is not permitted to get deltaVector with difference frame");
		}
		Vector retVec = new Vector(size);
		for (int i = 0 ; i < size ; i++ )	{
			retVec.setParameter (i ,  getParameter(i) + target.getParameter(i)) ;
		}
		return retVec;
	}
	public Vector getMinus(Vector target)	{
		if (this.getSize() != target.getSize())	{
			throw new RuntimeException("It is not permitted to get deltaVector with difference frame");
		}
		Vector retVec = new Vector(size);
		for (int i = 0 ; i < size ; i++ )	{
			retVec.setParameter (i ,  getParameter(i) - target.getParameter(i)) ;
		}
		return retVec;
	}
	public Vector getConstMulti(double constValue)	{
		Vector retVec = new Vector(size);
		for (int i = 0 ; i < size ; i++ )	{
			retVec.setParameter (i ,  getParameter(i)*constValue) ;
		}
		return retVec;
	}	


}
