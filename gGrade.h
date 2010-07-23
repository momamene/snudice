#pragma once

#define MAXSUBJECT 6

class gGrade {
public:
	int		m_subjectN;
	int		m_subject[MAXSUBJECT];
	int		m_meetCount[MAXSUBJECT];
	int		m_weightCount[MAXSUBJECT];
	
public:
	void init ();
	double gradeMinOne (int n);
	double gradeExpectOne (int n);
	double gradeAverage ();
	void meet(int subjectIndex);
};