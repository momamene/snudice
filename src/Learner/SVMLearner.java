package Learner;

import java.util.ArrayList;

import ElementPackage.DataVector;

public class SVMLearner {
	private ArrayList<DataVector> data;
	private OptimizeFramework optimizer;
	
	
	public SVMLearner()	{
		data = new ArrayList();
		optimizer = new Optimizer01();
	}
	public void setHyperplane()	{
		
	}
	//bad Design....T.T
	public void Optimize()	{
		setOptiRmizerVector();
		getOptimizer().optimize();
	}
	
	public void setOptiRmizerVector() {

		optimizer.setVectorList(data);
	}

	public void addData(DataVector parameter)	{
		data.add(parameter);
	}
	
	public void setOptiRmizer(OptimizeFramework optimizer) {
		this.optimizer = optimizer;
	}
	public OptimizeFramework getOptimizer() {
		return optimizer;
	}
}
