import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.File;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;
import java.io.PrintWriter;

import ElementPackage.ConstForSVM;
import ElementPackage.DataVector;
import ElementPackage.Hyperplane;
import ElementPackage.SpaceVector;
import Learner.SVMLearner;



public class SVMTestor {
	
	private static int inputCount = 0;
	
	public static void main(String[] ar)	{
		String lineString;
		String linkEE = "C:\\패턴1,2\\패턴2\\패턴2";

		BufferedReader buf;
		SVMLearner svmLearner = new SVMLearner();
		DataVector dataVector;
		
		int frame = 0;
		
		SpaceVector preSp = new SpaceVector(0,0,9.8);
		try {
			PrintWriter print_writer = new PrintWriter (new BufferedWriter(new FileWriter(new File("Linkout2.txt"))) , true);
			for (int i=0;i<10;i++)	{
				frame = 0;
			
				inputCount = 0;
				dataVector = new DataVector(ConstForSVM.MAXFRAME);
			
				String link = linkEE + "_acc(" + (i+1) + ")" + ".txt";
				buf = new BufferedReader(new FileReader(link));
				print_writer.println("link : " + link);
				
				while((lineString=buf.readLine()) != null)	{
					frame ++;
					
					String splitted[] = lineString.split(" ");
					Double accx=Double.parseDouble(splitted[1]);
					Double accy=Double.parseDouble(splitted[2]);
					Double accz=Double.parseDouble(splitted[3]);
					
//					System.out.println(frame + "번째 프레임 의 좌표 : (" + + accx + "," + accy + "," + accz + ")");
					
					SpaceVector sv = new SpaceVector(accx,accy,accz);
					
					if ( ( preSp.getMinus(sv).getX() > ConstForSVM.AccelPermittedLimit ||
						preSp.getMinus(sv).getY()  > ConstForSVM.AccelPermittedLimit ||
						preSp.getMinus(sv).getZ()  > ConstForSVM.AccelPermittedLimit ) &&
						inputCount == 0)	{
						inputCount ++ ;
					}
					if (inputCount > 0)	{
						if ( !dataVector.addVector( sv ) )	{
							svmLearner.addData(dataVector);
							print_writer.println("받은 데이터 ...");
							for (int j=0;j< dataVector.getFrame() * SpaceVector.size() ; j++)	{
								print_writer.print(dataVector.getParameter(j)+ ", ");
							}
							print_writer.println("");							print_writer.println("-----");

							break;
						}
					}
					preSp = sv;
				}
			}
		}
			 catch (IOException e) {
					System.out.println("File not found");
			 }

		svmLearner.Optimize();
		Hyperplane resHp = svmLearner.getOptimizer().getHyperplane();
		try	{
			PrintWriter print_writer = new PrintWriter (new BufferedWriter(new FileWriter(new File("out1.txt"))) , true);
			print_writer.println("Gradiant");
			for (int i=0;i< resHp.getGradiant().getFrame() * SpaceVector.size() ; i++)	{
				print_writer.println(resHp.getGradiant().getParameter(i));
			}
			print_writer.println("Bias");
			print_writer.println(resHp.getBias());
		} catch(IOException e) {;}

	}
}
