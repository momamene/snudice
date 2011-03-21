package ElementPackage;


public class DataVector extends Vector{
	
	private int frame;
	private int index;
	private Pattern label;
	
	
	public DataVector(int frame , Pattern label)	{
		super(frame * ConstForSVM.SPACEDIMENSION);
		this.setFrame(frame);
		setParameter(new double[frame * ConstForSVM.SPACEDIMENSION]);
		setLabel(label);
		index = 0;
	}
	
	public void erase()	{
		index = 0;
	}
	public void setFrame(int frame) {
		this.frame = frame;
	}

	public int getFrame() {
		return frame;
	}
	
	public boolean addVector(SpaceVector p)	{
		if (index == frame * ConstForSVM.SPACEDIMENSION)	{
			return false;
		}
		setParameter(index++ , p.getX() );
		setParameter(index++ , p.getY() );
		setParameter(index++ , p.getZ() );
		return true;
	}
	public void setLabel(Pattern label) {
		this.label = label;
	}
	public Pattern getLabel() {
		return label;
	}

}
