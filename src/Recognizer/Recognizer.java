package Recognizer;

import java.util.ArrayList;

import ElementPackage.ConstForSVM;
import ElementPackage.DataVector;
import ElementPackage.Hyperplane;
import ElementPackage.SpaceVector;



public class Recognizer {
	private DataVector dataVector;
	private ArrayList<Hyperplane> classifyFuncList;
	private DataVector preSp;
	//inputCount의 역할 : open 된 후부터  Count 한다.
 
	private static int inputCount;
	
	Recognizer()	{
		inputCount = 0;
		dataVector = new DataVector(ConstForSVM.MAXFRAME);
	}
	
	private int recognize()	{
		return interprete( patternize() );
	}
	
	private int interprete(int[] pattern) {
		// TODO Auto-generated method stub
		int retVal = 0;
		for (int i = 0 ; i < pattern.length; i ++ )	{
			retVal += 2 * retVal + ( pattern[i] > 0 ? 1 : 0) ;
		}
		return retVal;
	}
	private int[] patternize() {
		int[] retArray = new int[ classifyFuncList.size() ];
		double value;
		Hyperplane pHyperIndex;
		for (int i = 0 ; i < classifyFuncList.size() ; i++ )	{
			pHyperIndex = classifyFuncList.get(i);
			value = pHyperIndex.getGradiant().getProduct(dataVector) +
					pHyperIndex.getBias();
			retArray[i] = value > 0.0f ? 1 : -1;
		}
		return retArray;
	}
	
	public int distinguish(int x,int y,int z)	{	// 이놈을 호출시키게 한다.
		SpaceVector sv = new SpaceVector(x, y, z);
		int retVal = -1;
		if ( (  sv.getMinus(sv).getX() < ConstForSVM.AccelPermittedLimit ||
				sv.getMinus(sv).getY() < ConstForSVM.AccelPermittedLimit ||
				sv.getMinus(sv).getZ() - 9.8f < ConstForSVM.AccelPermittedLimit ) &&
				inputCount > 0)	{
				inputCount = 0 ;
			}
		if ( (  sv.getMinus(sv).getX() > ConstForSVM.AccelPermittedLimit ||
				sv.getMinus(sv).getY() > ConstForSVM.AccelPermittedLimit ||
				sv.getMinus(sv).getZ() - 9.8f > ConstForSVM.AccelPermittedLimit ) &&
				inputCount == 0)	{
				inputCount ++ ;
			}
		if (inputCount > 0)	{
			if ( !dataVector.addVector( sv ) )	{
				retVal =  recognize();
			dataVector.erase();
			}
		}
			
		return retVal;
	}
	public void addclassifyFuncList(Hyperplane hyperPlane)		{
		classifyFuncList.add( hyperPlane );
	}
}



