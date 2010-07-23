#include "gGrade.h"
#include "gGameCore.h"

void gGrade::init(){
	m_subjectN=0;
}

double gGrade::gradeMinOne (int n){
	double grade;
	grade = m_weightCount[n] / 50;
	if(grade>4.3) grade = 4.3;
	return grade;
}
double gGrade::gradeExpectOne (int n){
	gGameCore *gameCore = gGameCore::GetIF();
	double grade;
	if(gameCore->m_turnN==0) return 3.0;
	else{
		grade = m_weightCount[n] / gameCore->m_turnN;
	}
	if(grade>4.3) grade = 4.3;
	return grade;	
}
double gGrade::gradeAverage (){
	double average = 0.0;
	for (int i = 0 ; i < m_subjectN ; i++ ) {
		average += gradeExpectOne(i);
	}
	average = average/7;
	return average;
}