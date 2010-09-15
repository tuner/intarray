<?php

/** 
 * Intarray is an "optimized" array of integers.
 * Arrays are exposed to PHP as strings, so they are cheap to serialize.
 *
 * @author Kari Lavikka <kari.lavikka@dynamoid.com>
 * @package intarray
 */

if (false) {

/** Create an intarray of defined size.
 * Intarray values are initialized with 0.
 *
 * @param int $length Size of new intarray.
 * @return string New intarray.
 */
function intarray_create($length) {}

/** Create an intarray from PHP-array.
 * Intarray is created from values of the array. Given array is not recursed.
 * Values of array are stored in ascending order without duplicates.
 * Keys are not preserved.
 *
 * @param array $array Array to be converted to intarray.
 * @return string Intarray created from given array.
 */
function intarray_create_from_array($array) {}

/** Returns a sorted version of an intarray. Removes duplicates if "uniq" is true.
 * You can use this function to convert a random intarray to a valid "set" for
 * operations like binary search, intersect, union, etc...
 *
 * @param string $intarray Intarray to be sorted.
 * @param bool $uniq Whether to remove duplicates.
 * @return string Sorted intarray.
 */
function intarray_sort($intarray, $uniq = false) {}

/** Inserts a value to intarray at "index". Rest of the array is shifted and
 * array is expanded if "expand" is true. Otherwise the last value is dropped.
 *
 * @param string $intarray Intarray.
 * @param int $index Insert index.
 * @param int $value Insert value.
 * @param bool $expand Whether to expand.
 */
function intarray_insert(&$intarray, $index, $value, $expand = true) {}

/** Adds a value to a sorted intarray. Returns the index of newly added value
 * or -1 if it was already present.
 *
 * @param string $intarray
 * @param int $value
 * @return int
 */
function intarray_add(&$intarray, $value) {}

/** Deletes an item at "index" from intarray. If "contract" is true the array
 * is contracted, otherwise a trailing zero is set. Returns the deleted value.
 *
 * @param string $intarray
 * @param int $index
 * @param bool $contract
 * @return int
 */
function intarray_delete(&$intarray, $index, $contract = true) {}

/** Sets value at index in intarray. 
 *
 * @param string $intarray
 * @param int $index
 * @param int $value
 */
function intarray_set(&$intarray, $index, $value) {}

/** Gets value from intarray.
 *
 * @param string $intarray
 * @param int $index
 * @return int Value.
 */
function intarray_get($intarray, $index) {}

/** Returns a new intarray of (length) from (offset).
 * If offset is negative it is count from the end.
 * If length is negative it points to the last element.
 *
 * @param string $intarray
 * @param int $offset
 * @param int $length
 * @return string Sliced intarray.
 */
function intarray_slice($intarray, $offset, $length = 0xffffffff) {}

/** Returns length of an intarray.
 *
 * @param string $intarray
 * @return int
 */
function intarray_length($intarray) {}

/** Returns a randomly shuffled version of an intarray.
 * 
 * @param string $intarray
 * @return string
 */
function intarray_shuffle($intarray) {}

/** Performs a binary search on a sorted intarray.
 * If intarray is not sorted result is undefined.
 *
 * @param string $intarray
 * @param int $needle
 * @return int Index of element where the needle should be, false on error.
 */
function intarray_binarysearch_slot($intarray, $needle) {}

/** Performs a binary search on a sorted intarray.
 * If intarray is not sorted result is undefined.
 *
 * @param string $intarray
 * @param int $needle
 * @return int Index of needle or -1 if not found.
 */
function intarray_binarysearch($intarray, $needle) {}

/** Performs a linear search on an intarray.
 *
 * @param string $intarray
 * @param int $needle
 * @param int $start start searching from this index, if negative start from length - start index.
 * @return int Index of needle or -1 if not found.
 */
function intarray_search($intarray, $needle, $start = 0) {}

/** Returns an intersection of two sorted intarrays.
 *
 * @param string $a
 * @param string $b
 * @return string a /\ b.
 */
function intarray_intersect($a, $b) {}

/** Returns an union of two sorted intarrays.
 *
 * @param string $a
 * @param string $b
 * @return string a U b.
 */
function intarray_union($a, $b) {}


/** Returns a relative complement of two intarrays.
 * Elements present in array A but without element in array B 
 *
 * @param string $a
 * @param string $b
 * @return string a \ b.
 */
function intarray_difference($a, $b) {}

/** Returns a symmetric difference (XOR) of two sorted intarrays. 
 * Elements present in array A and B but not in both.
 * union(A,B) \ intersect(A,B).
 *
 * @param string $a
 * @param string $b
 * @return string a ^ b.
 * @link http://en.wikipedia.org/wiki/Symmetric_difference
 */
function intarray_symmetric_difference($a, $b) {}

/** Dumps an intarray to the output.
 *
 * @param string $intarray
 */
function intarray_dump($intarray) {}

/** Returns contens of an intarray as JSON string.
 *
 * @param string $intarray
 * @return string
 */
function intarray_to_json($intarray) {}


/**
 * Checks if the given string is a valid intarray.
 *
 * @param string $intarray Intarray string
 * @param integer $index Optional check is value at index is valid, -1 to omit check.
 * @return boolean
 */
function intarray_check($intarray, $index = -1) {}
}

