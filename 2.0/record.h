#ifndef RECORD_H
#define RECORD_H

#include "patient.h"
#include "doctor.h"
#include "treatment.h"

struct record {
	struct patient pa;
	struct doctor * doc;
	struct treatment tm;
	struct record * next;
};

struct record_list {
	struct record * head;
};

#endif