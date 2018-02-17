//
//  Properties.h
//  SCMap
//
//  Created by Zach Zahos on 2018-02-04.
//

#pragma once

#define GETTER(__type__, __name__) \
	__type__ __name__ ; \
public: \
	__type__ get_ ## __name__ () \
		{ return this-> __name__ ; } \
private:

#define SETTER(__type__, __name__) \
	__type__ __name__ ; \
public: \
	void set_ ## __name__ ( __type__ newValue) \
		{ this-> __name__ = newValue; } \
private:

#define GET_SET(__type__, __name__) \
	__type__ __name__ ; \
public: \
	__type__ get_ ## __name__ () \
		{ return this-> __name__ ; } \
	void set_ ## __name__ ( __type__ newValue) \
		{ this-> __name__ = newValue; } \
private:

#define get_SET(__type__, __name__) \
	__type__ __name__ ; \
public: \
	__type__ get_ ## __name__ (); \
	void set_ ## __name__ ( __type__ newValue) \
		{ this-> __name__ = newValue; } \
private:

#define GET_set(__type__, __name__) \
	__type__ __name__ ; \
public: \
	__type__ get_ ## __name__ () \
		{ return this-> __name__ ; } \
	void set_ ## __name__ ( __type__ newValue); \
private:

