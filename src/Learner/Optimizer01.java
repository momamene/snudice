package Learner;

import java.io.BufferedWriter;
import java.io.File;
import java.io.FileWriter;
import java.io.PrintWriter;
import java.util.Iterator;

import ElementPackage.ConstForSVM;
import ElementPackage.DataVector;
import ElementPackage.Vector;

public class Optimizer01 extends OptimizeFramework {

	@Override
	public void optimize() {
		// TODO Auto-generated method stub
		double minDist = vectorList.get(0).distance(vectorList.get(1));
		
		DataVector iDV , jDV;
		for (Iterator<DataVector> i = vectorList.listIterator() ; i.hasNext() ; )	{
			iDV = i.next();
			for (Iterator<DataVector> j = vectorList.listIterator() ; j.hasNext() ; )	{
				jDV = j.next();
				
				double dist = getDistance( iDV , jDV );
				if (dist < 0.00000000000001)	{
					continue;
				}
				
				if ( minDist > dist )	{
					minDist = dist;
					setSupportVector ( iDV , jDV );
				}
			}
		}
		
		try	{
			PrintWriter print_writer = new PrintWriter (new BufferedWriter(new FileWriter(new File("SVout1.txt"))) , true);
			print_writer.println("minDist : " + minDist);
			print_writer.println("SupportVectorList : ");
			print_writer.println("dataVector : ");
			for (int j=0;j< ConstForSVM.getVectorSize() ;j++)
				print_writer.print(SupportVectorList.get(0).getParameter(j) + ",");
			print_writer.println("------------------------------------");
			
			for (int j=0;j<ConstForSVM.getVectorSize() ;j++)
				print_writer.print(SupportVectorList.get(1).getParameter(j) + ",");
			print_writer.println("------------------------------------");
		} catch(Exception e){;}


		makeHyperplane();
	}
	private void setSupportVector(DataVector A, DataVector B)	{
		eraseSupportVector();
		addSupportVector(A);
		addSupportVector(B);
	}
	private double getDistance(Vector A, Vector B)	{
		return A.distance(B);
	}

	private void makeHyperplane()	{
		Vector delta = SupportVectorList.get(0).getDeltaVector(SupportVectorList.get(1));
		Vector middlePoint = SupportVectorList.get(0).getPlus(SupportVectorList.get(1)).getConstMulti(0.5f);
		System.out.println("delta : ");
		System.out.println("middlePoint : ");
		hyperplane.setGradiant(delta);
		hyperplane.setBias( - delta.getProduct(middlePoint));
	}
}

