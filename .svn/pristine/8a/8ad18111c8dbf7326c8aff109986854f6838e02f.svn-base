#include "LoaderCorePrivate.h"

#include "RsaPss.h"
#include "TomMacros.h"


/**
* Size of the salt we'll use for initial version. 
*/
#define SIZE_SALT 32

/*! 
 * \def LC_RSA_LEAST_SIG_INDEX
 * \brief Index to least significant byte of a lc_long_num
 * 
 * Big endian, so always larger than the index to the most significant byte
 */
#define LC_RSA_LEAST_SIG_INDEX ((LC_RSA_MAX_LEN_BITS/32)-1)

/*! 
 * \def LC_RSA_MOST_SIG_INDEX
 * \brief Index to most significant byte of a lc_long_num
 * 
 * Big endian, so always smaller than the index to the least significant byte
 */
#define LC_RSA_MOST_SIG_INDEX  (0)


#define countof(a) (sizeof(a)/sizeof(*(a)))

void  ClearLN( pkcs_long_num * const number );
void  MultInvLN(  pkcs_long_num * const output , 
				const pkcs_long_num * const m , 
				const pkcs_long_num * const a );

void  ModBase2LN(       pkcs_long_num * const remainder , 
				 pkcs_long_num * const x ,
				 lc_uint32       bitPos );
void  InvertLN(         pkcs_long_num * const output , 
			   const pkcs_long_num * const in );

lc_bool  AddLN(         pkcs_long_num * const output , 
			   const pkcs_long_num * const in1 , 
			   const pkcs_long_num * const in2 );
void  SubLN(            pkcs_long_num * const output , 
			const pkcs_long_num * const in1 , 
			const pkcs_long_num * const in2 );

void  CopyLN(   pkcs_long_num * const output , 
			 const pkcs_long_num * const in );

void  InvertLN(         pkcs_long_num * const output , 
			   const pkcs_long_num * const in );

void  MontExpLN(        pkcs_long_num * const output , 
				const pkcs_long_num * const n , 
				const pkcs_long_num * const e ,
				const pkcs_long_num * const m );

void  MultLN(           pkcs_long_num * const output , 
			 const pkcs_long_num * const x , 
			 const pkcs_long_num * const y );

//

#define LC_RSA_MEMMOVE LongMath_memmove

/* If LC_RSA_MAX_LEN_BITS is not a multiple of 32, then the pkcs_long_num will contain 
* too few bits, as (LC_RSA_MAX_LEN_BITS/32) 32 bit values are allocated and the 
* integer arithmetic means that any bits over the multiple of 32 will be lost
*/
#if (LC_RSA_MAX_LEN_BITS == 0) || ((LC_RSA_MAX_LEN_BITS%32) != 0)
#error "The value of LC_RSA_MAX_LEN_BITS must be a multiple of 32, and be greater"\
	" than zero"
#endif

/*vernon*/
static void * LongMath_memmove(void * destination, const void * source, lc_uint32 num)
{
	lc_uchar *ptr1 = (lc_uchar *)destination;
	lc_uchar *ptr2 = (lc_uchar *)source;
	lc_uint32 i=0;
	lc_sint32 inc = 1;
	if (ptr1 > ptr2)
	{
		/** need to traverse backwards instead of forwards to avoid stomping over values you haven't
		* copied yet. */
		ptr1 += num-1;
		ptr2 += num-1;
		inc = -1;
	}
	/** now iterate forwards or backwards and copy each byte */
	for(i=0; i<num; ++i)
	{
		*ptr1 = *ptr2;
		ptr1 += inc;
		ptr2 += inc;
	}

	return destination;
}

//
/*
* \def IS_BIT_SET
* \brief Macro to test whether bit bitPos of longNum lNum is 1
* 
* Result of call is the bit whose value was requested, so 1 or 0 is returned
*/
#define IS_BIT_SET(lNum,bitPos)\
	(lNum).num[LC_RSA_LEAST_SIG_INDEX-((bitPos)/32)] & (1<<((bitPos)%32))


//********* function declaration**************************//

static lc_bool isEqualIntLN(const pkcs_long_num * const in1 , 
							const lc_uint32       in2 );

static lc_bool isNegLN(     const pkcs_long_num * const in );

static lc_bool isZeroLN(    const pkcs_long_num * const in );

static void shiftRightPadLN(      pkcs_long_num * const output , 
							const pkcs_long_num * const in , 
							const lc_uint32       positions );

static lc_bool isNegOneLN(  const pkcs_long_num * const in );

static void addIntLN(             pkcs_long_num * const output , 
					 const pkcs_long_num * const in1 , 
					 const lc_uint32       in2 );

static lc_bool gteLN(       const pkcs_long_num * const in1 , 
					 const pkcs_long_num * const in2 );

static void gcdLN(                pkcs_long_num * const output , 
				  pkcs_long_num * const C , 
				  pkcs_long_num * const D , 
				  pkcs_long_num         x , 
				  pkcs_long_num         y );


static lc_bool isPower2LN(        lc_uint32 *     bitPos , 
						  const pkcs_long_num * const in );

static lc_uint32 calcMostSigElem( const pkcs_long_num *in );

static lc_uint32 mult2Int(        lc_uint32 *     outLo ,
						  lc_uint32       in1 , 
						  lc_uint32       in2 );

static void divLN(                pkcs_long_num * const quotient ,
				  pkcs_long_num * const remainder ,
				  pkcs_long_num         x , 
				  const pkcs_long_num * const y );

static void shiftLeftLN(          pkcs_long_num * const output , 
						const pkcs_long_num * const in , 
						const lc_uint32       positions );

static void shiftRightLN(         pkcs_long_num * const output , 
						 const pkcs_long_num * const in , 
						 const lc_uint32       positions );

static void squareLN(           pkcs_long_num * const output , 
					 const pkcs_long_num * const x);

static void montRedLN(            pkcs_long_num * const output , 
					  const pkcs_long_num * const m , 
					  const lc_uint32 *     mp , 
					  const pkcs_long_num * const T  , 
					  const lc_uint32       n );

static void montMultLN(           pkcs_long_num * const output , 
					   const pkcs_long_num * const x , 
					   const pkcs_long_num * const y , 
					   const pkcs_long_num * const m , 
					   const lc_uint32       mp );

static void multIntLN(            pkcs_long_num * const output , 
					  const pkcs_long_num * const in1 , 
					  const lc_uint32       in2 );

// ***************function definition************************//
/*!
* \brief Determine whether the value of pkcs_long_num in is equal to an lc_uint32 
*        value
* 
* Verify whether the value of a pkcs_long_num is equal to a lc_uint32 value by 
* confirming that all elements other than the least significant element are set 
* to 0.  Verify that the least significant element is equal to the lc_uint32 input 
* value.
* 
* @param in1 Location of a pkcs_long_num
* @param in2 lc_uint32 value to compare pkcs_long_num to
* 
* @return LC_TRUE if values are equal
* @return LC_FALSE if values are not equal
*/
static lc_bool isEqualIntLN(const pkcs_long_num * const in1 , 
							const lc_uint32       in2 )
{
	lc_uint32 counter = LC_RSA_MOST_SIG_INDEX;

	for(  ; counter < LC_RSA_LEAST_SIG_INDEX ; ++counter )
	{
		/* if the value of this element is not 0, then the value represented by the 
		* pkcs_long_num is larger than the maximum value of the input integer
		*/
		if( in1->num[counter] )
		{
			return LC_FALSE;
		}
	}

	if( in1->num[counter] == in2 )
	{
		return LC_TRUE;
	}

	return LC_FALSE;
}

/*!
* \brief Determine whether pkcs_long_num in is negative
* 
* Determine whether a pkcs_long_num value is negative by checking whether its most 
* significant bit is 1 or 0.
* 
* It is a basic check, but it should work as we know where to expect an 
* unusually large positive integer which causes this bit to be set, and where 
* to expect a negative integer which would cause this function to be called to 
* determine whether a value is negative or not
* 
* @param in Location of input pkcs_long_num
* 
* @return LC_TRUE If most significant bit is 1
* @return LC_FALSE If most significant bit is 0
*/
static lc_bool isNegLN(     const pkcs_long_num * const in )
{
	if( ((lc_uint32)1 << (LC_RSA_ELEM_LEN_BITS-1)) & in->num[LC_RSA_MOST_SIG_INDEX] )
	{
		return LC_TRUE;
	}
	return LC_FALSE;
}

/*!
* \brief Adds two multiple precision integers
* 
* Adds multiple precision numbers, and returns a boolean which states whether 
* overflow has occurred during the addition.
* 
* The pointer output can point to the same variable as in1 and the 
* operation of the function will not be affected. E.g. the function can be 
* called using:
*   LongMath_addLN( &a , &a , &b );
* 
* @param in1    Location of first number to add
* @param in2    Location of second number to add
* @param output Location of location to store the result
* 
* @return LC_TRUE if overflow occurred during addition
* @return LC_FALSE if no overflow occurred
*/
lc_bool  AddLN(             pkcs_long_num * const output , 
			   const pkcs_long_num * const in1 , 
			   const pkcs_long_num * const in2 )
{
	lc_bool carry = LC_FALSE;
	lc_sint32 counter = 0;

	for( counter = LC_RSA_LEAST_SIG_INDEX ; counter >= LC_RSA_MOST_SIG_INDEX ; --counter )
	{
		output->num[counter] = in1->num[counter] + in2->num[counter];

		if( LC_FALSE == carry )
		{
			if( output->num[counter] < in2->num[counter] )
			{
				carry = LC_TRUE;
			}
		}
		else
		{
			/* add carry.  if result is greater than one of the inputs to the addition 
			* then overflow did not occur, so set carry to LC_FALSE
			*/
			++output->num[counter];
			if( output->num[counter] > in2->num[counter] )
			{
				carry = LC_FALSE;
			}
		}
	}

	return carry;
}

/*!
* \brief Determine whether pkcs_long_num in is Zero
* 
* Test whether pkcs_long_num in has any non-zero elements
* 
* @param in Location of pkcs_long_num to test
* 
* @return LC_TRUE if pkcs_long_num is zero
* @return LC_FALSE if pkcs_long_num is not zero
*/
static lc_bool isZeroLN(    const pkcs_long_num * const in )
{
	lc_sint32 counter = LC_RSA_LEAST_SIG_INDEX;

	for(  ; counter >= LC_RSA_MOST_SIG_INDEX ; --counter )
	{
		if( in->num[counter] )
		{
			return LC_FALSE;
		}
	}

	return LC_TRUE;
}

/*!
* \brief Determine if the value of pkcs_long_num in is -1
* 
* @param in Location of value to check
* 
* @return LC_TRUE If the value is -1
* @return LC_FALSE If the value is not -1
*/
static lc_bool isNegOneLN(  const pkcs_long_num * const in )
{
	lc_uint32 counter = 0;

	for(  ; counter < (LC_RSA_MAX_LEN_BITS/LC_RSA_ELEM_LEN_BITS) ; ++counter )
	{
		if( 0xffffffff != in->num[counter] )
		{
			return LC_FALSE;
		}
	}

	return LC_TRUE;
}

/*!
* \brief Subtracts one multiple precision integer from another
* 
* Subtracts one multiple precision integer from another by adding one number 
* to the twos compliment of the other.
* 
* output = in1 - in2
* 
* The values of in1 and in2 are not changed during the subtraction, therefore 
* the location of output can be the same as the location of in1 and/or in2.
* 
* @param output Location to store the result
* @param in1    Location of the input integer to be subtracted from
* @param in2    Location of the input integer to subtract from in1
*/
void  SubLN(                pkcs_long_num * const output , 
			const pkcs_long_num * const in1 , 
			const pkcs_long_num * const in2 )
{
	pkcs_long_num temp; 

	InvertLN( &temp , in2 );
	AddLN( output , in1 , &temp );

	addIntLN( output , output , 1 );
}

/*!
* \brief Invert all bits in a pkcs_long_num variable
* 
* Invert all bits in a pkcs_long_num variable.  This is used during subtraction, when 
* the actual operation is an addition of a negative number.  The negative 
* number is calculated by inverting then incrementing the result
* 
* As this function operates on an element by element basis, parameters in and 
* output can point to the same location.
* 
* @param output Location to store result
* @param in     Location of source pkcs_long_num
*/
void  InvertLN(             pkcs_long_num * const output , 
			   const pkcs_long_num * const in )
{
	register lc_sint32 counter = 0;

	for( counter = LC_RSA_LEAST_SIG_INDEX ; counter >= LC_RSA_MOST_SIG_INDEX ; --counter )
	{
		output->num[counter] = ~(in->num[counter]);
	}
}


/*!
* \brief Adds a multiple precision integer to a 32bit integer
* 
* Adds a multiple precision integer to a 32 bit integer, and returns a boolean 
* which states whether overflow has occurred during the addition.
* 
* The pointer output can point to the same variable as in1 and the 
* operation of the function will not be affected. E.g. the function can be 
* called using:
*   addIntLN( &a , &a , b );
* 
* @param in1    Location of multiprecision integer to add
* @param in2    32 bit integer to add
* @param output Location to store the result
* 
* @return LC_TRUE if overflow occurred during addition
* @return LC_FALSE if no overflow occurred
*/
static void addIntLN(             pkcs_long_num * const output , 
					 const pkcs_long_num * const in1 , 
					 const lc_uint32       in2 )
{
	lc_bool carry = LC_FALSE;
	lc_sint32 counter = 0;

	output->num[LC_RSA_LEAST_SIG_INDEX] = in1->num[LC_RSA_LEAST_SIG_INDEX] + in2;

	if( output->num[LC_RSA_LEAST_SIG_INDEX] < in2 )
	{
		/* rollover occurred */
		carry = LC_TRUE;
	}

	for( counter = LC_RSA_LEAST_SIG_INDEX-1 ; (LC_TRUE == carry) && (counter >= LC_RSA_MOST_SIG_INDEX) ; --counter )
	{
		output->num[counter] = in1->num[counter] + 1;

		/* if the element is 0, then overflow occurred (as we have only added 1), 
		* otherwise no rollover so carry is set LC_FALSE
		*/
		if( output->num[counter] )
		{
			carry = LC_FALSE;
		}
	}

	/* if the counter value is not -1 then we stopped early, and only copy if the 
	* input and output locations are different, otherwise the operation is 
	* unnecessarySubLN
	*/
	if( ( counter >= LC_RSA_MOST_SIG_INDEX ) && ( output != in1 ) )
	{
		LC_memcpy( output->num , in1->num , 4*(counter+1) );
	}
}

/*!
* \brief Calculate whether in1 >= in2
* 
* Calculate whether in1 >= in2 by iterating through each element
* 
* @param in1 Location of a pkcs_long_num
* @param in2 Location of a pkcs_long_num
* 
* @return LC_TRUE If in1 >= in2
* @return LC_FALSE If in1 < in2
*/
static lc_bool gteLN(       const pkcs_long_num * const in1 , 
					 const pkcs_long_num * const in2 )
{
	lc_uint32 counter;

	for( counter = LC_RSA_MOST_SIG_INDEX ; counter <= LC_RSA_LEAST_SIG_INDEX ; ++counter )
	{
		if( (in1->num[counter]) > (in2->num[counter]) )
		{
			return LC_TRUE;
		}
		else if( (in1->num[counter]) < (in2->num[counter]) )
		{
			return LC_FALSE;
		}
	}

	return LC_TRUE;
}

/*!
* \brief Shift a pkcs_long_num right, making the MSB less significant and pad the 
*        new MSBs
* 
* Shift pkcs_long_num in right, making the original MSB "positions" binary digits 
* less significant and "losing" what were originally the "positions" least 
* significant digits.
* 
* The new Most Significant Bits are padded using what was originally the most 
* significant bit.  E.g. if it was originally 1 then all the new MSBs will also 
* be 1, and if it was 0 then the new MSBs will be 0.
* 
* This allows division to be performed by a power of 2 by shifting, even on 
* negative numbers
* 
* @param output Location to store the result
* @param in     Location of value to be shifted
* @param positions Number of bits to shift input value by
*/
static void shiftRightPadLN(      pkcs_long_num * const output , 
							const pkcs_long_num * const in , 
							const lc_uint32       positions )
{
	lc_bool isNeg = LC_FALSE; /* LC_TRUE if input value is negative */
	lc_uint32 bitsToShift = positions%LC_RSA_ELEM_LEN_BITS;
	lc_uint32 elemsToShift = positions/LC_RSA_ELEM_LEN_BITS;
	lc_uint32 temp = 0;

	lc_sint32 counter = 0;

	if( LC_TRUE == isNegLN( in ) )
	{
		isNeg = LC_TRUE;

		/* if the input value is -1, then divided by 2 it will equal 0 */
		if( LC_TRUE == isNegOneLN( in ) )
		{
			ClearLN( output );
			return;
		}
	}

	for( counter = LC_RSA_LEAST_SIG_INDEX - elemsToShift ; counter >= LC_RSA_MOST_SIG_INDEX ; --counter )
	{
		/* copy upper bits */
		temp = in->num[counter] >> bitsToShift;

		/* if we are not going to go out of bounds... */
		if( bitsToShift )
		{
			if( counter != LC_RSA_MOST_SIG_INDEX )
			{
				temp |= in->num[counter-1] << (LC_RSA_ELEM_LEN_BITS - bitsToShift);
			}
			else if( LC_TRUE == isNeg )
			{
				temp |= 0xff << (LC_RSA_ELEM_LEN_BITS - bitsToShift);
			}
		}
		output->num[counter+elemsToShift] = temp;
	}

	if( elemsToShift )
	{
		for( counter = (LC_RSA_MOST_SIG_INDEX + elemsToShift)-1 ; counter >= LC_RSA_MOST_SIG_INDEX ; --counter )
		{
			if( LC_TRUE == isNeg )
			{
				output->num[counter] = 0xffffffff;
			}
			else
			{
				output->num[counter] = 0;
			}
		}
	}
}


/*!
* \brief Determine whether in is a power of 2, and specify it's MSB set
* 
* This function determines whether a multiprecision integer is a power of 2, 
* and specifies the most significant bit of the value which is set high.
* 
* For example if the input value is 0100 then the return value would be LC_TRUE, 
* and bitPos would equal 2.  
* 
* Even if the input is known not to be a power2 value, the function can still 
* be useful in finding the most significant bit set in order to iterate around 
* a loop a suitable number of times for example.
* 
* If no bits are set, LC_FALSE is returned from the function and the value of 
* bitPos is set to -1.  As bitPos is unsigned this becomes 0xffffffff.
* 
* @param bitPos Location where the index to the most significant set bit is 
*               stored
* @param in Location of multiprecision integer input
* 
* @return LC_TRUE if in is a power of 2
* @return LC_FALSE if in is not a power of 2, or no bits set
*/
static lc_bool isPower2LN(        lc_uint32 * bitPos , 
						  const pkcs_long_num * const in )
{
	lc_uint32 counter = LC_RSA_MOST_SIG_INDEX;
	lc_uchar bit = 0;

	lc_uchar bitCount = 0;

	*bitPos = 0;

	for(  ; counter <= LC_RSA_LEAST_SIG_INDEX ; ++counter )
	{
		for( bit = LC_RSA_ELEM_LEN_BITS-1 ; 0xff != bit  ; --bit )
		{
			if( in->num[counter] & (1 << bit) )
			{
				if( bitCount )
				{
					return LC_FALSE;
				}
				else
				{
					bitCount = 1;
					*bitPos = bit + (LC_RSA_LEAST_SIG_INDEX-counter)*LC_RSA_ELEM_LEN_BITS;
				}
			}
		}
	}

	if( bitCount )
	{
		return LC_TRUE;
	}
	--*bitPos; /* make bitPos equal to 0xffffffff */
	return LC_FALSE; /* no bits set */
}

/*!
* \brief Calculate the most significant element of pkcs_long_num in
* 
* Calculates the most significant element of pkcs_long_num in, where an element is 
* the basic data type used in a pkcs_long_num (e.g. lc_uchar, lc_uint16, lc_uint32)
* 
* This function could be useful to help those that loop "for each bit", as this 
* function loops per element it could potentially reduce the number of bits 
* that the 'per bit' function loops for significantly
* 
* @param in Location of input pkcs_long_num
* 
* @return Index to the most significant non-zero element, 0 indicating the 
*         most significant digit
*/
static lc_uint32 calcMostSigElem( const pkcs_long_num *in )
{
	lc_uint32 i = LC_RSA_MOST_SIG_INDEX;

	for(  ; i <= LC_RSA_LEAST_SIG_INDEX ; ++i )
	{
		if( in->num[i] )
		{
			return i;
		}
	}

	return 0;
}

/**
* \brief Function to compute the inverse of a word in the ring Z/R, where R is 2^w.
*
* See "High-Speed RSA Implementation", Koc, TR-201, RSA Laboratories
*
* @param The number to compute the inverse of
* @param The w exponent in 2^w, that is, R
* @return x^{-1} mod 2^w
*/
static lc_uint32 ModInverse(lc_uint32 x, lc_uint32 w)
{
	lc_uint32 mask, y, p;
	lc_uint32 j;

	y = 1;
	mask = 0x3;
	p = 2;
	for (j=1; j<w; j++) {
		if (p < (x*y & mask))
			y += p;
		mask = (mask<<1) | 1;
		p <<= 1;
	}
	return y;
}

/*!
* \brief Multiply 2 single precision integers to produce a multiprecision 
*        result
* 
* Multiply two 32 bit integers to give a 64 bit product which is stored in 
* two 32 bit words
* 
* NOTE: The value of output is not set to 0 during the execution of this 
* function as it will likely be called multiple times.  If output is required 
* to be zeroed it should be done once in the calling function.
* 
* @param outLo Location to store lower 32 bits of result
* @param in1 First 32 bit integer to be multiplied
* @param in2 Second 32 bit integer to be multiplied
* 
* @return Value of upper 32 bit word of the multiplication result
*/
static lc_uint32 mult2Int(      lc_uint32     * outLo ,
						  lc_uint32       in1 , 
						  lc_uint32       in2 )
{
	lc_uint32 carry = 0;
	lc_uint32 inter1;
	lc_uint32 inter2;
	lc_uint32 outHi;

	lc_uint32 lo1 = (lc_uint16) in1; /* discard upper 16 bits */
	lc_uint32 hi1 = in1 >> 16;
	lc_uint32 lo2 = (lc_uint16) in2; /* discard upper 16 bits */
	lc_uint32 hi2 = in2 >> 16;

	/* initial value of low 32 bits */
	*outLo = lo1 * lo2;
	outHi = hi1 * hi2;

	/* middle 32 bits */
	inter1 = hi1 * lo2;
	inter2 = hi2 * lo1;

	inter1 += inter2;

	if( inter1 < inter2 )
	{
		/* roll over */
		carry = 0x10000;
	}

	*outLo += inter1 << 16;

	if( *outLo < (inter1 << 16 ) )
	{
		++carry;
	}

	inter1 >>= 16; /* discard lower bits */

	return(outHi + carry + inter1);
}

/*!
* \brief Multiply 2 multiprecision integer values
* 
* Multiply 2 multiprecision integer values using many single precision 
* multiplications. Each single precision multiplication produces a double 
* precision integer result which is added to the output pkcs_long_num.
* 
* The output location is used to store values during the calculation so cannot 
* point to the same object as one of the inputs
* 
* @param output Location to store the result
* @param x      Location of one of the input values to be multiplied
* @param y      Location of the other input value to be multiplied
*/
void  MultLN(               pkcs_long_num * const output , 
			 const pkcs_long_num * const x , 
			 const pkcs_long_num * const y )
{
	lc_uint32 c = 0;
	lc_uint32 hiWord = 0;
	lc_uint32 loWord = 0;
	lc_sint32 j = 0;
	lc_uint32 ij = 0; /* index for w_i+j */

	lc_sint32 i = LC_RSA_LEAST_SIG_INDEX;
	const lc_sint32 n = calcMostSigElem( x );
	const lc_sint32 t = calcMostSigElem( y );

	ClearLN( output );

	for(  ; i >= t ; --i )
	{
		c = 0;

		for( j = LC_RSA_LEAST_SIG_INDEX ; j >= n  ; --j )
		{
			ij = (i+j) - LC_RSA_LEAST_SIG_INDEX;

			hiWord = mult2Int( &loWord , x->num[j] , y->num[i] );

			loWord += output->num[ij];
			if( loWord < output->num[ij] )
			{
				++hiWord;
			}

			loWord += c;
			if( loWord < c )
			{
				++hiWord;
			}

			c = hiWord;
			output->num[ij] = loWord;
		}

		/* calculate i+n+1 index */
		ij = (i+j) - LC_RSA_LEAST_SIG_INDEX;
		output->num[ij] = c;
	}
}

/* 
* \brief Divide one pkcs_long_num by another and return the quotient and remainder in 
*        pkcs_long_num format
* 
* Divide a dividend pkcs_long_num by a divisor pkcs_long_num.  The divisor is shifted left 
* by decresing amounts (I.e. on the first iteration the shift left will be the 
* greatest and on the last iteration the shift will be by 0 places), and if the 
* shifted divisor is found to be less than or equal to the current value of the 
* dividend the shifted value of the divisor is subtrated from the divident.  
* The bit set in the quotient is equal to the number of bits the divisor was 
* shifted.
* 
* As x is passed by value, a pointer to the location of x can be provided as 
* the parameter for either the quotient of the remainder.
* 
* If either the divisor or dividend values are zero, the quotient and remainder 
* values will be set to zero and the function will return.
* 
* @param quotient Location to store the quotient of the division operation
* @param remainder Location to store the remainder of the division operation, 
*                  equivalent to performing: x modulus bitPos
* @param x Multiprecision integer dividend
* @param y Location of multiprecision integer divisor
* 
* Example:
* 
* dividend = 0b0110 0001 = 97
* divisor  = 0b0000 0010 =  2
* 
* The most significant bit of the dividend is the 6th bit (when numbered 0 to 
* 7) so n = 6+1 = 7, and the most significant bit of the divisor is the 1st bit 
* so t = 1+1 = 2.
* 
* counter = 7-2     = 5
*   shift divisor left by 5 places
*   shifted  = 0b0100 0000 = 64
*   
*   shifted < divisor
*     subtract shifted from divisor
*       divisor  = 0b0010 0001 = 33
*     set 'counter'th bit of the quotient
*       quotient = 0b0010 0000 = 32
* 
* counter = (7-2)-1 = 4
*   shift divisor left by 4 places
*   shifted = 0b0010 0000 = 32
* 
*   shifted < divisor
*     subtract shifted from divisor
*       divisor  = 0b0000 0001 = 1
*     set 'counter'th bit of the quotient
*       quotient = 0b0011 0000 = 48
* 
* The last iteration of this loop is counter == 0, following the last iteration 
*   dividend = 0b0000 0001 =  1
*   quotient = 0b0011 0000 = 48
* 
* Therefore:
*   remainder = 0b0000 0001 = 1
*/
static void divLN(                pkcs_long_num * const quotient ,
				  pkcs_long_num * const remainder ,
				  pkcs_long_num         x , 
				  const pkcs_long_num * const y )
{
	lc_sint32 n = -1;
	lc_sint32 t = -1;

	lc_sint32 counter = 0;

	pkcs_long_num inter;

	/* For counter = n to t, shift the divisor (y) left by (counter-t) bits.  If 
	* the shifted value is greater than the dividend (x) then set bit (counter-t) 
	* in the quotient and subtract the shifted value from the dividend.
	* 
	* Repeat until counter < t, the resulting value in the dividend (x) is the 
	* remainder
	*/

	/* calculate n
	* 
	* n is the index of the most significant non-zero digit of the dividend
	* t is the index of the most significant non-zero digit of the divisor
	* 
	* n >= t >= 1
	*/
	isPower2LN( (lc_uint32 *) &t , y );
	isPower2LN( (lc_uint32 *) &n , &x );

	++t;
	++n;

	ClearLN( quotient );

	if( ( 0 == n ) || ( 0 == t ) )
	{
		/* t or n had the value 0xffffffff when the isPower2LN function returned, 
		* which means that no bits of the pkcs_long_num were set to 1 (i.e. the pkcs_long_num 
		* is zero)
		*/
		ClearLN( remainder );
		return;
	}

	for( counter = n ; counter >= t ; --counter )
	{
		shiftLeftLN( &inter , y , counter-t );

		if( LC_TRUE == gteLN( &x , &inter) )
		{
			/* x >= tmp1 */
			SubLN( &x , &x , &inter );
			quotient->num[LC_RSA_LEAST_SIG_INDEX-((counter-t)/32)] = 1 << ((counter-t)%32);
		}
	}

	CopyLN( remainder , &x );
}

/*!
* \brief Shift a pkcs_long_num left, making the LSB more significant
* 
* in and output may specify the same memory locations, as the input value is 
* modified in such a way that corruption will not occur.
* 
* @param output Location to store result
* @param in Location of value to be shifted
* @param positions Number of bits to shift input value by
*/
static void shiftLeftLN(          pkcs_long_num * const output , 
						const pkcs_long_num * const in , 
						const lc_uint32       positions )
{
	lc_uint32 bitsToShift = positions%LC_RSA_ELEM_LEN_BITS;
	lc_uint32 elemsToShift = positions/LC_RSA_ELEM_LEN_BITS;
	lc_uint32 temp = 0;

	lc_uint32 counter = 0;

	if( !positions )
	{
		/* if we are asked to shift 0 places and the input and output locations are
		* different, copy the input value to the output value.  Otherwise is the 
		* locations are the same there is no need to copy
		*/
		if( output != in )
		{
			CopyLN( output , in );
		}
	}
	else if( positions >= LC_RSA_MAX_LEN_BITS )
	{
		/* if the number of positions to shift is larger than the number of bits in 
		* a pkcs_long_num, clear the pkcs_long_num so its value is 0
		*/
		ClearLN( output );
	}
	else if( bitsToShift )
	{
		for( counter = LC_RSA_MOST_SIG_INDEX + elemsToShift ; counter <= LC_RSA_LEAST_SIG_INDEX ; ++counter )
		{
			/* copy upper bits */
			temp = in->num[counter] << bitsToShift;

			/* if we are not going to go out of bounds... */
			if( counter != LC_RSA_LEAST_SIG_INDEX )
			{
				temp |= in->num[counter+1] >> (LC_RSA_ELEM_LEN_BITS - bitsToShift);
			}
			output->num[counter-elemsToShift] = temp;
		}

		if( elemsToShift )
		{
			LC_memset( &(output->num[LC_RSA_LEAST_SIG_INDEX - (elemsToShift-1)]) , 0 , elemsToShift*4 );
		}
	}
	else
	{
		/* bitsToShift = 0, only have to shift elements */
		if( output == in )
		{
			/* input and output buffers are the same so need to use LC_RSA_MEMMOVE */
			LC_RSA_MEMMOVE( output->num , &(in->num[elemsToShift]) , 4*(LC_RSA_LEAST_SIG_INDEX - (elemsToShift - 1)) );
		}
		else
		{
			/* input and output buffers are different, so use LC_memcpy */
			LC_memcpy( output->num , &(in->num[elemsToShift]) , 4*(LC_RSA_LEAST_SIG_INDEX - (elemsToShift - 1)) );
		}

		LC_memset( &(output->num[LC_RSA_LEAST_SIG_INDEX - (elemsToShift-1)]) , 0 , elemsToShift*4 );
	}
}
/*!
* \brief Shift a pkcs_long_num right, making the MSB less significant
* 
* in and output may specify the same memory locations, as the input value is 
* modified in such a way that corruption will not occur.
* 
* @param output Location to store result
* @param in Location of value to be shifted
* @param positions Number of bits to shift input value by
*/
static void shiftRightLN(         pkcs_long_num * const output , 
						 const pkcs_long_num * const in , 
						 const lc_uint32       positions )
{
	lc_uint32 bitsToShift = positions%LC_RSA_ELEM_LEN_BITS;
	lc_uint32 elemsToShift = positions/LC_RSA_ELEM_LEN_BITS;
	lc_uint32 temp = 0;

	lc_sint32 counter = 0;

	if( !positions )
	{
		if( output != in )
		{
			CopyLN( output , in );
		}
	}
	else if( positions >= LC_RSA_MAX_LEN_BITS )
	{
		ClearLN( output );
	}
	else
	{
		for( counter = LC_RSA_LEAST_SIG_INDEX - elemsToShift ; counter >= LC_RSA_MOST_SIG_INDEX ; --counter )
		{
			/* copy upper bits */
			temp = in->num[counter] >> bitsToShift;

			/* if we are not going to go out of bounds... */
			if( (counter != LC_RSA_MOST_SIG_INDEX) && (bitsToShift) )
			{
				temp |= in->num[counter-1] << (LC_RSA_ELEM_LEN_BITS - bitsToShift);
			}
			output->num[counter+elemsToShift] = temp;
		}

		if( elemsToShift )
		{
			for( counter = (LC_RSA_MOST_SIG_INDEX + elemsToShift)-1 ; counter >= LC_RSA_MOST_SIG_INDEX ; --counter )
			{
				output->num[counter] = 0;
			}
			/*   LC_memset( &(output->num[0]) , 0 , elemsToShift*4 );*/
		}
	}
}


/*!
* \brief Multiply a multiprecision integer with a 32 bit integer
* 
* Multiply a multiprecision integer and a 32 bit integer value using many 
* single precision multiplications. Each single precision multiplication 
* produces a double precision integer result which is added to the output 
* pkcs_long_num.
* 
* The output location is used to store values during the calculation so cannot 
* point to the same object as the multiprecision input
* 
* @param output Location to store the result
* @param x      Location of the multiprecision input value
* @param y      32 bit integer to be multiplied
*/
static void multIntLN(            pkcs_long_num * const output , 
					  const pkcs_long_num * const x ,
					  const lc_uint32       y )
{
	lc_uint32 c = 0;
	lc_uint32 hiWord = 0;
	lc_uint32 loWord = 0;
	lc_sint32 j = 0;
	const lc_sint32 n = calcMostSigElem( x );


	ClearLN( output );

	for( j = LC_RSA_LEAST_SIG_INDEX ; j >= n  ; --j )
	{
		hiWord = mult2Int( &loWord , x->num[j] , y );

		loWord += output->num[j];
		if( loWord < output->num[j] )
		{
			++hiWord;
		}

		loWord += c;
		if( loWord < c )
		{
			++hiWord;
		}

		c = hiWord;
		output->num[j] = loWord;
	}

	/* write the carry word from the last 2 integer multiply operation */
	output->num[j] = c;
}



#define BNI(bnp,i) (bnp->num[LC_RSA_LEAST_SIG_INDEX-(i)])
/**
* \brief Function to compute the square of a number.
*
* See HAC, 14.16
*
* @param  output   The square x^2
* @param  The number to square
*/
static void squareLN(       pkcs_long_num * const output , 
					 const pkcs_long_num * const x)
{
	lc_sint32 j = 0, i;

	lc_uint32 v=0, hiu=0, lou=0, hic=0, loc=0;

	lc_sint32 t = calcMostSigElem( x );
	t = LC_RSA_LEAST_SIG_INDEX - t +1;

	ClearLN( output );

	for (i=0; i<t; i++) {

		/** Step 2.1 **/

		/** x_i*x_i **/
		lou = mult2Int ( &v, BNI(x,i), BNI(x,i) );

		/** w_{2i} + x_i*x_i **/
		v += BNI(output, 2*i);
		if (v < BNI(output, 2*i))
			lou++;

		/** w_{2i} = v **/
		BNI(output, 2*i) = v;

		/** c <-- u **/
		hic = 0;
		loc = lou;

		/** Step 2.2 **/
		for (j=i+1; j<t; j++) {
			/** x_j * x_i **/
			hiu = 0;
			lou = mult2Int (&v, BNI(x,j), BNI(x,i));

			/** 2*x_i*x_j **/
			if (lou >>31) hiu++;
			lou<<=1;
			if (v >>31) lou++;
			v<<=1;

			/** 2*x_i*x_j + c **/
			v += loc;
			if (v < loc) {
				lou += 1;
				if (lou < 1)
					hiu++;
			}
			lou += hic;
			if (lou < hic) {
				hiu += 1;
			}

			/** w_{i+j} + 2*x_i*x_j + c **/
			v += BNI(output,i+j);
			if (v < BNI(output, i+j)) {
				lou += 1;
				if (lou < 1)
					hiu++;
			}

			BNI(output, i+j) = v;
			hic = hiu;
			loc = lou;
		}

		/** Step 2.3 **/
		for (; hic|loc; t++) {
			BNI(output, i+t) += loc;
			if (BNI(output, i+t) < loc)
				hic++;
			loc = hic;
			hic = 0;
		}
	}
}


/*!
* \brief Mongomery Reduction algorithm which provides efficient modulus 
*        functionality for multiprecision integers
* 
* Montgomery Reduction is a modular arithmetic algorithm which provides an 
* efficient method of modulusing multiprecision integers.  The operation 
* performs calculations using a Montgomery representation, and the output of 
* this function given an input T is T(R^-1) mod m, where R is b^n and n is the 
* number of digits used to represent the modulus.
* 
* The locations represented by output and other parameters cannot be equal as 
* output is used as temporary storage during the execution of the function.
* 
* NOTE: This algorithm has been implemented based on the description given in 
* section 14.32 of the Handbook of Applied Cryptography.
* 
* HOWEVER: It has been optimised specifically to work with a number base of 
* 2^32 which makes it's execution much more efficient as each digit (such as 
* ui) is a 32bit word.
* 
* @param output Location to store result of operation ( T(R^-1) mod m )
* @param m Location of modulus value
* @param mp Location of the value m' ( -(m^-1) mod b )
* @param T Location of the value which is to be modulus-ed
* @param n Number of base b digits in the value m
*/
static void montRedLN(            pkcs_long_num * const output , 
					  const pkcs_long_num * const m , 
					  const lc_uint32 * mp , 
					  const pkcs_long_num * const T  , 
					  const lc_uint32       n )
{
	lc_uint32 i = 0;
	lc_uint32 ui = 0;
	lc_uint32 shiftLen = 0;

	pkcs_long_num inter;

	/* A = T */
	CopyLN( output , T );

	for(  ; i < n ; ++i )
	{
		/* base 2^32 */
		/* u = ai * m' */
		/* can discard overflow as we only want the least significant element */
		ui = output->num[LC_RSA_LEAST_SIG_INDEX-i] * *mp;

		/* inter = m * ui */
		multIntLN( &inter , m , ui );

		/* inter = m * ui * b^i */
		shiftLeftLN( &inter , &inter , shiftLen );
		shiftLen += LC_RSA_ELEM_LEN_BITS;

		/* A = A + (ui * m * b^i) */
		AddLN( output , output , &inter );
	}

	/* A = A /(b^n) */
	shiftRightLN( output , output , shiftLen );

	if( LC_TRUE == gteLN( output , m ) )
	{
		SubLN( output , output , m );
	}
}



/*!
* \brief Implements Montgoery Multiplication functionality
*/
static void montMultLN(           pkcs_long_num * const output , 
					   const pkcs_long_num * const x , 
					   const pkcs_long_num * const y , 
					   const pkcs_long_num * const m , 
					   const lc_uint32       mp )
{
	lc_uint16 i = 0;
	lc_uint32 ui = 0;
	lc_uint16 mDigits = 0;

	pkcs_long_num inter1;
	pkcs_long_num inter2;

	ClearLN( output );

	mDigits = (lc_uint16)(LC_RSA_LEAST_SIG_INDEX - (calcMostSigElem( m ) - 1));

	for(  ; i < mDigits ; ++i )
	{
		/* all ui calculations are single precision because the result is mod b */

		/* ui = x[i] * y[0] */
		ui = y->num[LC_RSA_LEAST_SIG_INDEX] * x->num[LC_RSA_LEAST_SIG_INDEX-i];

		/* ui = A[0] + (x[i] * y[0]) */
		ui += output->num[LC_RSA_LEAST_SIG_INDEX];

		/* ui = ( (A0 + x[i] * y[0])*mp ) mod b */
		ui *= mp;

		/* A calculations are multi-precision */

		/* A = A + x[i] * y */
		multIntLN( &inter1 , y , x->num[LC_RSA_LEAST_SIG_INDEX-i] );
		multIntLN( &inter2 , m , ui );
		AddLN( &inter2 , &inter2 , &inter1 );

		/* A = A + x[i] * y + ui * m */
		AddLN( output , output , &inter2 );

		/* A = (A + x[i] * y + ui * m) / b */
		shiftRightLN( output , output , LC_RSA_ELEM_LEN_BITS );
	}

	if( LC_TRUE == gteLN( output , m ) )
	{
		SubLN( output , output , m );
	}
}

//*******************************//

/*!
* \brief Sets the value of a pkcs_long_num to 0
* 
* Clears the value of a pkcs_long_num, all bits are set to 0 which represents the 
* value 0.
* 
* @param in Location of the pkcs_long_num to be zeroed
*/
void  ClearLN(pkcs_long_num * const in )
{
	LC_memset( in->num , 0 , LC_RSA_MAX_LEN_BITS/8 );
}
//
///*!
//* \brief Sets the value of a pkcs_long_num to 0
//* 
//* Clears the value of a pkcs_long_num, all bits are set to 0 which represents the 
//* value 0.
//* 
//* @param in Location of the pkcs_long_num to be zeroed
//*/
//void  ClearLN(pkcs_long_num * const in )
//{
//	LC_memset( in->num , 0 , LC_RSA_MAX_LEN_BITS/8 );
//}


/*!
* \brief Calculate the multiplicative inverse of two longNums
* 
* Calculate the multiplicative inverse of 2 longNums.  The algorithm calculates 
* which pkcs_long_num is the greatest, and uses that as the modulo value.
* 
* The aim of the algorithm is to find a number z, which will give:
*   1 == xz mod y
* Where x is the smaller of the 2 parameters supplied, and z is the larger.
* 
* This algorithm is based on algorithm 14.64 of the Handbook of Applied 
* Cryptography
* 
* @param output Location to store the multiplicative inverse
* @param m Location of the modulus pkcs_long_num
* @param a Location of a positive pkcs_long_num to calculate the multiplicative 
*          inverse of
*/

void  MultInvLN(            pkcs_long_num * const output , 
				const pkcs_long_num * const m , 
				const pkcs_long_num * const a )
{
	pkcs_long_num C;
	pkcs_long_num D;

	gcdLN( output , &C , &D , *m , *a );

	/* if the GCD is 1, then there is a multiplicative inverse value.  We can use 
	* the value of D to calculate it
	*/
	if( LC_TRUE == isEqualIntLN( output , 1 ) )
	{
		/* test if D is negative by testing if the most significant bit it set.
		* Although pkcs_long_num is unsigned by default this should be a sensible test
		*/
		if( LC_TRUE == isNegLN( &D ) )
		{
			AddLN( &D , &D , m );
		}

		/* return multiplicative inverse */
		CopyLN( output , &D );
	}
	else
	{
		/* no multiplicative inverse, so set output to 0 */
		ClearLN( output );
	}
}

/*!
* \brief Calculate greatest common divisor of 2 longNums
* 
* Calculates the greatest common divisor of 2 multiple precision numbers using 
* the Binary Extended GCD algorithm (14.61) specified in the Handbook Of 
* Applied Cryptography.
* 
* Although values C and D are not the computed result, they are used by other 
* algorithms in the pkcs_long_num 'library' as they give additional information about 
* the GCD calculation.
* 
* @param output Location of the GCD of values x and y
* @param C Location of intermediate value C
* @param D Location of intermediate value D
* @param x First positive integer pkcs_long_num to use to find the GCD
* @param y Second positive integer pkcs_long_num to use to find the GCD
*/
static void gcdLN(                pkcs_long_num * const output , 
				  pkcs_long_num * const C , 
				  pkcs_long_num * const D , 
				  pkcs_long_num x , 
				  pkcs_long_num y )
{
	pkcs_long_num u;
	pkcs_long_num v;
	pkcs_long_num A;
	pkcs_long_num B;

	ClearLN( output );
	ClearLN( &A );
	ClearLN( &B );
	ClearLN( C );
	ClearLN( D );

	/* Step 1 */
	output->num[LC_RSA_LEAST_SIG_INDEX] = 1;

	/* Step 2 */
	/* While x and y are even 
	* 
	* This will never occur during RSA encryption
	*/

	/* Step 3 */
	/* B and C are already 0 */
	CopyLN( &u , &x );
	CopyLN( &v , &y );
	A.num[LC_RSA_LEAST_SIG_INDEX] = 1;
	D->num[LC_RSA_LEAST_SIG_INDEX] = 1;

	while( LC_FALSE == isZeroLN( &u ) )
	{
		/* Step 4 */
		/* while u is even */
		while( !(u.num[LC_RSA_LEAST_SIG_INDEX] & 1) )
		{
			/* Step 4.1 */
			shiftRightPadLN( &u , &u , 1 ); /* divide by 2 */

			/* Step 4.2 */
			if( (!(A.num[LC_RSA_LEAST_SIG_INDEX] & 1)) && !(B.num[LC_RSA_LEAST_SIG_INDEX] & 1) )
			{
				/* A = A/2; B = B/2 */
				shiftRightPadLN( &A , &A , 1 ); /* divide by 2 */
				shiftRightPadLN( &B , &B , 1 ); /* divide by 2 */
			}
			else
			{
				/* A = (A+y)/2; B = (B-x)/2 */
				AddLN( &A , &A , &y );
				shiftRightPadLN( &A , &A , 1 );
				SubLN( &B , &B , &x );
				shiftRightPadLN( &B , &B , 1 );
			}
		}

		/* Step 5 */
		/* while v is even */
		while( !(v.num[LC_RSA_LEAST_SIG_INDEX] & 1) )
		{
			/* Step 5.1 */
			/* v = v/2 */
			shiftRightPadLN( &v , &v , 1 );

			/* Step 5.2 */
			if( (!(C->num[LC_RSA_LEAST_SIG_INDEX] & 1)) && !(D->num[LC_RSA_LEAST_SIG_INDEX] & 1) )
			{
				/* C = C/2; D = D/2 */
				shiftRightPadLN( C , C , 1 ); /* divide by 2 */
				shiftRightPadLN( D , D , 1 ); /* divide by 2 */
			}
			else
			{
				/* C = (C+y)/2; D = (D-x)/2 */
				AddLN( C , C , &y );
				shiftRightPadLN( C , C , 1 );
				SubLN( D , D , &x );
				shiftRightPadLN( D , D , 1 );
			}
		}

		/* Step 6 */
		/* If u >= v */
		if( LC_TRUE == gteLN( &u , &v ) )
		{
			/* u >= v */
			SubLN( &u , &u , &v );
			SubLN( &A , &A , C );
			SubLN( &B , &B , D );
		}
		else
		{
			/* u < v */
			SubLN( &v , &v , &u );
			SubLN( C , C , &A );
			SubLN( D , D , &B );
		}
	}

	/* Step 7 */
	/* if we get here, u == 0 
	* 
	* output will always be 1 as step 2 is omitted, so no need to multiply
	*/
	CopyLN( output , &v );
}


/*!
* \brief Calculate remainder of a number divided by a power of 2
* 
* Given the position of the single 1 bit position of a power of 2, this 
* function will divide a multiprecision integer value by the power of 2 that 
* the bit's position represents.  E.g. if bitPos = 8, 2^8 is 256, so the value 
* of x will be divided by 256.
* 
* The pointer to the location of x can be provided as the parameter for the 
* remainder, as it is not modified during the calculation.
* 
* @param remainder Location to store the remainder of the division operation
* @param x Multiprecision integer dividend
* @param bitPos Position of single high bit in the divisor
*/
void  ModBase2LN(           pkcs_long_num * const remainder , 
				 pkcs_long_num * const x ,
				 lc_uint32       bitPos )
{
	lc_uint32 mask = 0xffffffff;

	CopyLN( remainder , x );
	LC_memset( &(remainder->num[0]) , 0 , ((LC_RSA_MAX_LEN_BITS-bitPos)/LC_RSA_ELEM_LEN_BITS)*4 );
	remainder->num[LC_RSA_LEAST_SIG_INDEX-(bitPos/LC_RSA_ELEM_LEN_BITS)] &= mask >> (LC_RSA_ELEM_LEN_BITS-bitPos);
}


/*!
* \brief Invert all bits in a pkcs_long_num variable
* 
* Invert all bits in a pkcs_long_num variable.  This is used during subtraction, when 
* the actual operation is an addition of a negative number.  The negative 
* number is calculated by inverting then incrementing the result
* 
* As this function operates on an element by element basis, parameters in and 
* output can point to the same location.
* 
* @param output Location to store result
* @param in     Location of source pkcs_long_num
*/
//void  InvertLN(             pkcs_long_num * const output , 
//			   const pkcs_long_num * const in )
//{
//	register lc_sint32 counter = 0;
//
//	for( counter = LC_RSA_LEAST_SIG_INDEX ; counter >= LC_RSA_MOST_SIG_INDEX ; --counter )
//	{
//		output->num[counter] = ~(in->num[counter]);
//	}
//}


/*!
* \brief Function to perform a Montgomery Exponentiation
* 
* Mongomery Exponentiation is a modular arithmetic algorithm used to raise an 
* integer to a large power modulus a specified value.  Using normal techniques 
* such as repeated multiplication followed by a modulus, the intermediate 
* values can become very large and potentially overflow the data structure 
* which they are stored in.  Montgomery Exponentiation overcomes this by 
* performing an efficient modulus operation following each multiplication, 
* which prevents overflow.
* 
* The function uses repeated multiplications and Montgomery Reduction 
* operations to calculate the result.  Montgomery Reduction must be used 
* with standard multiplication rather than replacing both with Montgomery 
* Multiplication because the Multiplication algorithm does not support the case 
* where the input values are equal.
* 
* The locations represented by output and other parameters cannot be equal as 
* output is used as temporary storage during the execution of the function.
* 
* This algorithm has been implemented based on the description given in section 
* 14.94 of the Handbook of Applied Cryptography 
* 
* @param output Location to store result of operation (M^e) mod n
* @param n Location of modulus value
* @param e Location of exponent
* @param M Location of value to be raised to the power of the exponent
*/
void  MontExpLN(            pkcs_long_num * const output , 
				const pkcs_long_num * const n , 
				const pkcs_long_num * const e ,
				const pkcs_long_num * const M )
{
	lc_sint32 i = 0; /* counter */
	lc_uint32 k = 0;
	lc_uint32 l = 0;
	lc_uint32 n0p = 0;

	pkcs_long_num temp, temp2, one, R, Mm, Xm;

	/* calculate k = the number of significant bits in e = 1 + ceil(log_2 e) */
	isPower2LN( &k , e );
	k++;

	/* Compute R */
	ClearLN(&R);
	l = calcMostSigElem( n );
	R.num[l-1] = 1;

	/* Compute one */
	ClearLN(&one);
	one.num[LC_RSA_LEAST_SIG_INDEX] = 1;

	/* Step 1. Compute n'0 */
	//n0p = -ModInverse(n->num[LC_RSA_LEAST_SIG_INDEX], 32);
	n0p = 0-ModInverse(n->num[LC_RSA_LEAST_SIG_INDEX], 32);

	/* Step 2. Mm = M*R mod n */
	MultLN( &temp, M, &R);
	divLN( &temp2, &Mm, temp, n);

	/* Step 3. Xm = 1*R mod n */
	divLN( &temp2, &Xm, R, n);

	/* Step 4. Cycle from i=k-1 down to 0 */
	/* Where k is the number of significant bits in e **/
	for (i=k-1; i>=0; i--) {

		/* Step 5. Xm = ModPro(Xm, Xm) */
		squareLN( &temp, &Xm);
		montRedLN(&temp2, n , &n0p, &temp , LC_RSA_LEAST_SIG_INDEX - (l-1));

		/* Step 6. if (e_i is set) Xm = ModPro(Mm, Xm */
		if (IS_BIT_SET(*e, i)) {
			montMultLN( &Xm, &Mm, &temp2, n, n0p);
		} else {
			CopyLN( &Xm , &temp2 );
		}
	}

	/* Step 7. result = ModPro(Xm, 1) */
	montMultLN( output, &Xm, &one, n, n0p);
}

/*!
* \brief Copies the value of pkcs_long_num in to pkcs_long_num output
* 
* Copies the value of pkcs_long_num in to pkcs_long_num output.
* 
* This function uses a version of memcpy(), so the memory areas of pkcs_long_num 
* in and pkcs_long_num output should not overlap, otherwise unexpected behaviour may 
* occur.
* 
* @param output Location of destination pkcs_long_num
* @param in     Location of source pkcs_long_num to be copied
*/
void  CopyLN(               pkcs_long_num * const output , 
			 const pkcs_long_num * const in )
{
	LC_memcpy( output->num , in->num , LC_RSA_MAX_LEN_BITS/8 );
}


//***************signature verify operation***************************//


/*
 *
 */
static lc_uint32 Rsa_CountBits(
	const pkcs_long_num *pLongNum);


/*
 * RSA Verification Primitive 
 */
 static pkcs_result Rsa_VP2(
    const LC_RSA_key *pRsaKey,
    const pkcs_long_num *ps,
    pkcs_long_num *pm);

 /*
  * PSS Verificatiton Primitive
  */
 static pkcs_result Rsa_EmsaPssVerifySha256(
    const lc_buffer_st *pMessage,
    const lc_uchar em[SIGNATURE_LENGTH],
    lc_uint32 emBits);
 
 /*
  *
 */
 pkcs_result lc_CheckType_Bytes(
	const lc_buffer_st *pBytes);


 static pkcs_result Rsa_MGF1Sha256(
    const lc_buffer_st *pSeed,
    lc_uint32 maskLen, /** no more than SIGNATURE_LENGTH */
    lc_uchar *pMask);

 static void Rsa_Crypt( 
    pkcs_long_num *output, 
    const pkcs_long_num *input, 
    const LC_RSA_key *pRsaKey);


pkcs_result  Rsa_VerifyPssSha256(
	const lc_buffer_st *pHash,
	const lc_uchar signature[SIGNATURE_LENGTH],
	const LC_RSA_key *pRsaKey)
{


	pkcs_result result = PKCS_ERROR_SUCCESS;
	pkcs_long_num s;     
	pkcs_long_num m;     
	lc_uchar em[SIGNATURE_LENGTH]; 
	lc_uint32 emLen = 0;    
	lc_uint32 modBits = 0;   


	/*
	1. Length checking: If the length of the signature S is not k octets,
	output "invalid signature" and stop.
	-- This is actually a precondition of this function, so no check here.
	*/

	/* 2. RSA verification:

	a. Convert the signature S to an integer signature representative
	s (see Section 4.2):

	s = OS2IP (S).
	*/


	if (PKCS_ERROR_SUCCESS == result)
	{
		/**
		* Calculate length of modulus, in bits
		*/
		modBits = Rsa_CountBits(&pRsaKey->n);
        
        LoaderCoreSPI_take_a_break();
		result = Rsa_OS2IP(
			signature,
			SIGNATURE_LENGTH,
			&s);
	}

	/*
	b. Apply the RSAVP1 verification primitive (Section 5.2.2) to the
	RSA public key (n, e) and the signature representative s to
	produce an integer message representative m:

	m = RSAVP1 ((n, e), s).

	If RSAVP1 output "signature representative out of range,"
	output "invalid signature" and stop.
	*/

	if (PKCS_ERROR_SUCCESS == result)
	{
		result = Rsa_VP2(
			pRsaKey,
			&s,
			&m);
	}

	/**
	c. Convert the message representative m to an encoded message EM
	of length emLen = \ceil ((modBits - 1)/8) octets, where modBits
	is the length in bits of the RSA modulus n (see Section 4.1):

	EM = I2OSP (m, emLen).

	Note that emLen will be one less than k if modBits - 1 is
	divisible by 8 and equal to k otherwise.  If I2OSP outputs
	"integer too large," output "invalid signature" and stop.
	*/
	if (PKCS_ERROR_SUCCESS == result)
	{
		emLen = ((modBits-1) / 8);
		if ((modBits-1) % 8)
		{
			++emLen;
		}
		result = Rsa_I2OSP(
			&m,
			em,
			emLen);
	}

	/**
	3. EMSA-PSS verification: Apply the EMSA-PSS verification operation
	(Section 9.1.2) to the message M and the encoded message EM to
	determine whether they are consistent:

	Result = EMSA-PSS-VERIFY (M, EM, modBits - 1).
	4. If Result = "consistent," output "valid signature." Otherwise,
	output "invalid signature."
	*/
	if (PKCS_ERROR_SUCCESS == result)
	{
		result = Rsa_EmsaPssVerifySha256(
			pHash,
			em,
			modBits-1);
	}

	return result;





}

/**********************************************************/

void  Rsa_CalcMPrime( 
	const pkcs_long_num *n,
	pkcs_long_num *mp)
{
	pkcs_long_num base;
	pkcs_long_num temp;

	ClearLN( &base );

	base.num[LC_RSA_LEAST_SIG_INDEX-1] = 1;

	/* calculate m' (aka mp) = (-m^-1) mod b */
	MultInvLN( mp , &base , n );
    LoaderCoreSPI_take_a_break();
	ModBase2LN( mp , mp , 32 ); /* take modulus base 2^32 */
    LoaderCoreSPI_take_a_break();
	InvertLN( mp , mp );
    LoaderCoreSPI_take_a_break();
	ClearLN( &temp );
    LoaderCoreSPI_take_a_break();

	temp.num[LC_RSA_LEAST_SIG_INDEX-1] = 1;
	temp.num[LC_RSA_LEAST_SIG_INDEX] = 1; /* temp = 2^32 + 1 */

	AddLN( mp , &temp , mp );

}

/*******************Simple bit counter.*****************************/

static lc_uint32 Rsa_CountBits(
	const pkcs_long_num *pLongNum)
{
	lc_uint32 count = 0;
	lc_uint32 i = 0;
	lc_uint32 cur = 0;
	for (i=0; i<countof(pLongNum->num); ++i)
	{
		cur = pLongNum->num[i];
		if (cur != 0)
		{
			while (cur != 0)
			{
				cur >>= 1;
				++count;
			}
			count += (countof(pLongNum->num) - i - 1) * LC_RSA_ELEM_LEN_BITS;
			break;
		}
	}
	return count;
}

/**************basic OS2IP Function*********************************/
pkcs_result Rsa_OS2IP(
	const lc_uchar *pValue,
	lc_uint32 valueLen,
	pkcs_long_num *pLongNum)
{
	pkcs_result result = PKCS_ERROR_SUCCESS;
	lc_uint32 i = 0;
	lc_uint32 wi = 0;
	lc_uint32 shift = 0;

	if (!pValue
		|| !valueLen
		|| !pLongNum)
	{
		result = PKCS_ERROR_NULL_PARAM;
	}
	else if (valueLen >= countof(pLongNum->num)*sizeof(lc_uint32))
	{
		result = PKCS_ERROR_INVALID_LENGTH;
	}
	else
	{
		/**
		* initialize the output to 0
		*/
		LC_memset(
			pLongNum, 
			0,
			sizeof(*pLongNum));

		/**
		* shove all the values to the LSB of the destination number, 
		*/
		for (i=0; i<valueLen; ++i)
		{
			wi = countof(pLongNum->num) - ((valueLen - i - 1) / 4) - 1;
			#ifdef ENDIAN_LITTLE		
							shift = (3- (i % 4) ) * 8;

			#endif
			#ifdef ENDIAN_BIG
							shift = ((i % 4) ) * 8; 
			#endif			
			pLongNum->num[wi] |= pValue[i] << shift;
		}
        
        LoaderCoreSPI_take_a_break();
	}

	return result;
}

/*************************************************/
static void Rsa_Crypt( 
	pkcs_long_num *output, 
	const pkcs_long_num *input, 
	const LC_RSA_key *pRsaKey)
{
	/*pkcs_long_num base;

	ClearLN( output );
	ClearLN( &base );*/

	/*base.num[LC_RSA_LEAST_SIG_INDEX-1] = 1; *//* base 2^32 calculations */

	/*LongMath_montExpLN( output , &pRsaKey->n , &pRsaKey->mp , &pRsaKey->d_or_e , input , &base );*/

	ClearLN( output );

	MontExpLN( output, &pRsaKey->n, &pRsaKey->d_or_e, input);
}

/************** * RSA Verification Primitive *********************************/
static pkcs_result Rsa_VP2(
	const LC_RSA_key *pRsaKey,
	const pkcs_long_num *ps,
	pkcs_long_num *pm)
{
	pkcs_result result = PKCS_ERROR_SUCCESS;
	lc_uint32 i = 0;

	if (!pRsaKey
		|| !ps
		|| !pm)
	{
		result = PKCS_ERROR_NULL_PARAM;
	}

	/*   1. If the signature representative s is not between 0 and n - 1,
	output "signature representative out of range" and stop.*/
	if (PKCS_ERROR_SUCCESS == result)
	{
		result = PKCS_ERROR_SIGNATURE_VERIFICATION;

		for (i=0; i<countof(ps->num); ++i)
		{
			if (ps->num[i] < pRsaKey->n.num[i])
			{
				/**
				* we're within range, regardless of rest of bits.
				*/
				result = PKCS_ERROR_SUCCESS;
				break;
			}
			else if (ps->num[i] > pRsaKey->n.num[i])
			{
				/**
				* We're out of range
				*/
				break;
			}
			/* otherwise, we're equal so far */
		}
	}

	/*   2. Let m = s^e mod n. */
	/*   3. Output m. */
	if (PKCS_ERROR_SUCCESS == result)
	{
		Rsa_Crypt(
			pm,
			ps,
			pRsaKey);
	}


	return result;
}

/**********************************************************************/



/**************basic I2OSP Function*********************************/
pkcs_result Rsa_I2OSP(
	const pkcs_long_num *pLongNum,
	lc_uchar *pValue,
	lc_uint32 valueLen)
{
	pkcs_result result = PKCS_ERROR_SUCCESS;
	lc_uint32 bytes = 0;
	lc_uint32 vali = 0;
	lc_uint32 i = 0;
	lc_uint32 wi = 0;
	lc_uint32 shift = 0;

	if (!pLongNum
		|| !pValue
		|| !valueLen)
	{
		result = PKCS_ERROR_NULL_PARAM;
	}

	if (PKCS_ERROR_SUCCESS == result)
	{
		/* decide how many bytes are needed to store the value */
		bytes = Rsa_CountBits(pLongNum);
		if (bytes % 8)
		{
			bytes /= 8;
			++bytes;
		}
		else
		{
			bytes /= 8;
		}
		if (valueLen < bytes)
		{
			/**
			* Oh no! We can't possibly fit this number into our output. 
			* But in this case it means an invalid signature.
			*/
			result = PKCS_ERROR_SIGNATURE_VERIFICATION;
		}
	}

	if (PKCS_ERROR_SUCCESS == result)
	{
		LC_memset(pValue, 0, valueLen);
		for (vali=0; vali < bytes; ++vali)
		{
			i = valueLen - (bytes - vali);

			wi = countof(pLongNum->num) - ((valueLen - i - 1) / 4) - 1;
		
			#ifdef ENDIAN_LITTLE		
            shift = (3- (i % 4) ) * 8;	
			#endif
			#ifdef ENDIAN_BIG
						shift = ((i % 4) ) * 8; 
			#endif
			pValue[i] = (lc_uchar)((pLongNum->num[wi] & (0xFF << shift)) >> shift);
		}
	}

	return result;
}

/**************PSS Verificatiton Primitive *************************/

static pkcs_result Rsa_EmsaPssVerifySha256(
	const lc_buffer_st *pHash,
	const lc_uchar em[SIGNATURE_LENGTH],
	lc_uint32 emBits)
{
	pkcs_result result = PKCS_ERROR_SUCCESS;
	lc_uchar hashprime[SHA256_HASH_SIZE] = {0};

	lc_uint32 hLen = SHA256_HASH_SIZE;
	lc_uint32 sLen = SIZE_SALT;
	lc_buffer_st mHash = {0};
	lc_buffer_st maskedDB = {0};
	lc_buffer_st H = {0};
	lc_uint32 i = 0;
	lc_uint32 emLen = SIGNATURE_LENGTH;

	lc_uchar maskbytes[SIGNATURE_LENGTH] = {0};
	lc_buffer_st dbMask = {0};

	lc_uchar dbbytes[SIGNATURE_LENGTH] = {0};
	lc_buffer_st DB = {0};

	lc_buffer_st salt = {0};

	lc_uchar mprimebytes[SHA256_HASH_SIZE + SIZE_SALT + 8] = {0};

	lc_buffer_st Mprime = {0};

	/**
	* parameter validation
	*/
	result = lc_CheckType_Bytes( pHash );
	if (PKCS_ERROR_SUCCESS == result)
	{
		if (!em || !emBits)
		{
			result = PKCS_ERROR_NULL_PARAM;
		}
	}

	/*   1.  If the length of M is greater than the input limitation for the
	hash function (2^61 - 1 octets for SHA-1), output "inconsistent"
	and stop.*/

	/*   2.  Let mHash = Hash(M), an octet string of length hLen.*/
	//sha256_hash(pMessage, hash);
	mHash.bytes = pHash->bytes;
	mHash.length = SHA256_HASH_SIZE;


	/*   3.  If emLen < hLen + sLen + 2, output "inconsistent" and stop.*/
	if (PKCS_ERROR_SUCCESS == result && (emLen < hLen + sLen + 2))
	{
		result = PKCS_ERROR_SIGNATURE_VERIFICATION;
	}

	/*   4.  If the rightmost octet of EM does not have hexadecimal value
	0xbc, output "inconsistent" and stop.*/
	if (PKCS_ERROR_SUCCESS == result
		&& em[emLen-1] != 0xbc)
	{
		result = PKCS_ERROR_SIGNATURE_VERIFICATION;
	}


	/*   5.  Let maskedDB be the leftmost emLen - hLen - 1 octets of EM, and
	let H be the next hLen octets.*/
	if (PKCS_ERROR_SUCCESS == result)
	{
		maskedDB.bytes = (lc_uchar *)em;
		maskedDB.length = emLen - hLen - 1;
		H.bytes = maskedDB.bytes + maskedDB.length;
		H.length = hLen;
	}

	/*   6.  If the leftmost 8emLen - emBits bits of the leftmost octet in
	maskedDB are not all equal to zero, output "inconsistent" and
	stop.*/
	if (PKCS_ERROR_SUCCESS == result)
	{
		for (i=0; i<8*emLen - emBits; ++i)
		{
			lc_uint32 bytePos = i / 8;
			lc_uint32 bitPos = (7 - (i % 8));
			if (maskedDB.bytes[bytePos] & (1 << bitPos))
			{
				result = PKCS_ERROR_SIGNATURE_VERIFICATION;
			}
		}
	}

	/*   7.  Let dbMask = MGF(H, emLen - hLen - 1).*/
	if (PKCS_ERROR_SUCCESS == result)
	{
		dbMask.bytes = maskbytes;
		dbMask.length = emLen - hLen - 1;
		result = Rsa_MGF1Sha256(
			&H,
			dbMask.length,
			dbMask.bytes);
	}

	/*   8.  Let DB = maskedDB \xor dbMask.*/
	if (PKCS_ERROR_SUCCESS == result)
	{
		LC_ASSERT(maskedDB.length == dbMask.length); /** verify assumptions */
		DB.bytes = dbbytes;
		DB.length = maskedDB.length;
		for (i=0; i<maskedDB.length; ++i)
		{
			DB.bytes[i] = maskedDB.bytes[i] ^ dbMask.bytes[i];
		}

		/*   9.  Set the leftmost 8emLen - emBits bits of the leftmost octet in DB
		to zero.*/
		for (i=0; i<8*emLen - emBits; ++i)
		{
			lc_uint32 bytePos = i / 8;
			lc_uint32 bitPos = (7 - (i % 8));
			DB.bytes[bytePos] &= ~(1 << bitPos);
		}

		/*   10. If the emLen - hLen - sLen - 2 leftmost octets of DB are not zero
		or if the octet at position emLen - hLen - sLen - 1 (the leftmost
		position is "position 1") does not have hexadecimal value 0x01,
		output "inconsistent" and stop.

		!! peterm urk -- funny language -- leftmost is position 1 
		according to the above, so we need to actually look at 
		emLen - hLen - sLen - 2 for our 0x01 
		*/
		if (DB.bytes[emLen - hLen - sLen - 2] != 0x01)
		{
			result = PKCS_ERROR_SIGNATURE_VERIFICATION;
		}
		for (i=0; PKCS_ERROR_SUCCESS == result && i<emLen - hLen - sLen - 2; ++i)
		{
			if (DB.bytes[i] != 0)
			{
				result = PKCS_ERROR_SIGNATURE_VERIFICATION;
			}
		}
	}

	/*   11.  Let salt be the last sLen octets of DB.*/
	if (PKCS_ERROR_SUCCESS == result)
	{
		salt.bytes = DB.bytes + DB.length - sLen;
		salt.length = sLen;

		/*   12.  Let
		M' = (0x)00 00 00 00 00 00 00 00 || mHash || salt ;*/
		Mprime.bytes = mprimebytes;
		Mprime.length = sizeof(mprimebytes);

		LC_memcpy(
			Mprime.bytes + 8,
			mHash.bytes,
			mHash.length);
		LC_memcpy(
			Mprime.bytes + 8 + mHash.length,
			salt.bytes,
			salt.length);

		/*       M' is an octet string of length 8 + hLen + sLen with eight
		initial zero octets.*/

		/*   13. Let H' = Hash(M'), an octet string of length hLen.*/
		sha256_hash(
			&Mprime,
			hashprime);

		/*   14. If H = H', output "consistent." Otherwise, output "inconsistent."*/
		if (LC_memcmp(
			H.bytes,
			hashprime,
			H.length) != 0)
		{
			result = PKCS_ERROR_SIGNATURE_VERIFICATION;
		}
	}


	return result;
}

/*************************************************/
static pkcs_result Rsa_MGF1Sha256(
	const lc_buffer_st *pSeed,
	lc_uint32 maskLen, /** no more than SIGNATURE_LENGTH */
	lc_uchar *pMask)
{
	pkcs_result result = PKCS_ERROR_SUCCESS;
	lc_uint32 i = 0;
	lc_uint32 max = 0;
	lc_uint32 cur = 0;

	lc_uchar T[SIGNATURE_LENGTH*2] = {0}; /** for now we only deal with one signature size, so make a stack buf */

	lc_uchar htemp[SIGNATURE_LENGTH*2] = {0}; /** temporary buf for hash */ 

	/**
	* initialize first part of the htemp buffer, which doesn't change.
	*/
	LC_memcpy(
		htemp,
		pSeed->bytes,
		pSeed->length);

	/**
	* 1. If maskLen > 2^32 hLen, output "mask too long" and stop.
	*/
	/** Well, this is a very big number, beyond the scope of this variable, so we skip this check */

	/** 
	* 2. Let T be the empty octet string.
	*/ 

	/**
	* 3. For counter from 0 to \ceil (maskLen / hLen) - 1, do the
	following:
	*/
	max = (maskLen / SHA256_HASH_SIZE);
	if (maskLen % SHA256_HASH_SIZE)
	{
		++max;
	}

	/**
	* One of the preconditions of the function. We have a bit of a constrained implementation
	* here, so we'll take advantage of that.
	*/
	LC_ASSERT(max * SHA256_HASH_SIZE < SIGNATURE_LENGTH * 2);


	for (i=0; PKCS_ERROR_SUCCESS == result && i<max; ++i)
	{
		lc_uchar C[4];
		pkcs_long_num ilong;

		LC_memset(C, 0x0, sizeof(C));
		LC_memset(&ilong, 0x0, sizeof(pkcs_long_num));

		/**
		* a. Convert counter to an octet string C of length 4 octets (see
		* Section 4.1):
		*
		* C = I2OSP (counter, 4) .
		*/
		ilong.num[LC_RSA_LEAST_SIG_INDEX] = i;
		result = Rsa_I2OSP(
			&ilong,
			C,
			4);

		/**
		*    b. Concatenate the hash of the seed mgfSeed and C to the octet
		*  string T:
		*  T = T || Hash(mgfSeed || C) .
		*   
		*/
		if (PKCS_ERROR_SUCCESS == result)
		{
			lc_buffer_st tmp;
			tmp.bytes = htemp;
			tmp.length = pSeed->length + 4;
			LC_memcpy(
				htemp + pSeed->length,
				C,
				4);
			sha256_hash(
				&tmp,
				&T[cur]);
			cur += SHA256_HASH_SIZE;
		}
	}

	/**
	*  4. Output the leading maskLen octets of T as the octet string mask.
	*/
	if (PKCS_ERROR_SUCCESS == result)
	{
		LC_memcpy(pMask, T, maskLen);
	}

	return result;
}

/************************************************/
pkcs_result lc_CheckType_Bytes(
	const lc_buffer_st *pBytes)
{
	pkcs_result result = PKCS_ERROR_SUCCESS;

	/* Verify the input paramaters */
	if (LC_NULL == pBytes)
	{
		result = PKCS_ERROR_NULL_PARAM;
	}
	else
	{
		if (LC_NULL == pBytes->bytes || 0 == pBytes->length)
		{
			result = PKCS_ERROR_MISSING_DATA;
		}
	}

	return result;
}
