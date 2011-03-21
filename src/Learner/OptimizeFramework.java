package Learner;

import java.util.ArrayList;

import ElementPackage.DataVector;
import ElementPackage.Hyperplane;
import ElementPackage.Vector;

public abstract class OptimizeFramework {
	protected Hyperplane hyperplane;
	protected ArrayList<DataVector> vectorList;
	protected ArrayList<DataVector> SupportVectorList;

	public OptimizeFramework()	{
		SupportVectorList = new ArrayList();
		hyperplane = new Hyperplane();
	}
	public Hyperplane getHyperplane()	{
		return hyperplane;
	}
	public void printHyperplane()	{
		
	}
	
	public void addSupportVector(DataVector addedVector)	{
		SupportVectorList.add(addedVector);
	}
	public void eraseSupportVector()	{
		SupportVectorList.clear();
	}

	public abstract void optimize();
	public void setVectorList(ArrayList<DataVector> dataVector) {
		this.vectorList = dataVector;
	}
	public ArrayList<DataVector> getDataVecotr() {
		return vectorList;
	}

}

