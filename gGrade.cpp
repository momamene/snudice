#include "gGrade.h"
#include "gGameCore.h"
#include "tileContainer.h"

void gGrade::init()
{
	m_subjectN=0;
	for(int i = 0 ; i < MAXSUBJECT ; i ++)
	m_weightCount[i] = 90;
}

/*
double gGrade::gradeMinOne (int n)
{
	double grade;
	grade = (double)m_weightCount[n] / 50;
	if(grade>4.3) grade = 4.3;
	return grade;
}
*/
double gGrade::gradification (double grade){
	double gradeLeft = grade;
	if(grade<0.7 ) return 0.0;
	else if(grade >= 4.3) return 4.3;
	else{
		while(gradeLeft>1) gradeLeft -= 1.0;
		if(gradeLeft < 0.3) return grade - gradeLeft;
		else if(gradeLeft < 0.7) return grade - gradeLeft + 0.3;
		else return grade - gradeLeft + 0.7;
	}
}

double gGrade::gradeExpectOne (int n)
{
	gGameCore *gameCore = gGameCore::GetIF();
	double grade;
	//if(gameCore->m_turnN==1) return 3.0;
	//else{
		grade = (double)m_weightCount[n] / (gameCore->m_turnN+29);
	//}
	return gradification(grade);	
}

double gGrade::gradeAverage ()
{
	double average = 0.0;
	for (int i = 0 ; i < m_subjectN ; i++ ) {
		average += gradeExpectOne(i);
	}
	average = average/ m_subjectN;
	return average;
}

