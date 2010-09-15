--TEST--
intarray_create*
--SKIPIF--
<?php if (!extension_loaded("intarray")) print "skip"; ?>
--POST--
--GET--
--INI--
--FILE--
<?php 
if (!extension_loaded('intarray')) {
	dl('intarray.' . PHP_SHLIB_SUFFIX);
}

function test($test, $in, $out) {
	echo $test, $in === $out ? ' OK' : ' FAIL', "\n";
}

test('intarray_create', bin2hex(intarray_create(4)), '00000000000000000000000000000000');
test('intarray_create empty', bin2hex(intarray_create(0)), '');

/* big endian */
/*
test('intarray_create_from_array', bin2hex(intarray_create_from_array(array(1, 2, 3))), '000000010000000200000003');
test('intarray_create_from_array', bin2hex(intarray_create_from_array(array(3, 2, 1))), '000000010000000200000003');
test('intarray_create_from_array', bin2hex(intarray_create_from_array(array(3, 2, 1, 2, 3))), '000000010000000200000003');
*/

/* little endian */
test('intarray_create_from_array 1', bin2hex(intarray_create_from_array(array(1, 2, 3))), '010000000200000003000000');
test('intarray_create_from_array 2', bin2hex(intarray_create_from_array(array(3, 2, 1))), '010000000200000003000000');
test('intarray_create_from_array 3', bin2hex(intarray_create_from_array(array(3, 2, 1, 2, 3))), '010000000200000003000000');

/* empty */
test('intarray_create_from_array empty', bin2hex(intarray_create_from_array(array())), '');

/* fail */
error_reporting(0);
test('invalid_args_empty', intarray_create(), '');
echo $php_errormsg, "\n";
var_dump(intarray_create(-1));
echo $php_errormsg, "\n";
?>
--EXPECTF--
intarray_create OK
intarray_create empty OK
intarray_create_from_array 1 OK
intarray_create_from_array 2 OK
intarray_create_from_array 3 OK
intarray_create_from_array empty OK
invalid_args_empty OK
intarray_create() expects exactly %d parameter, %d given
bool(false)
Trying to create an intarray of %s
