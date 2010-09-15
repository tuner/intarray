--TEST--
intarray_check
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

echo "Normal intarray:\n";
$a = intarray_create_from_array(array(1, 2, 3, 4, 5));
var_dump(intarray_check($a));

echo "Empty intarray:\n";
$a = intarray_create(0);
var_dump(intarray_check($a));
intarray_insert($a, 0, 10, true);
var_dump(intarray_check($a));
intarray_insert($a, 1, 10, true);
var_dump(intarray_check($a));

echo "Empty string:\n";
var_dump(intarray_check(""));

echo "Check after set and insert:\n";
$a = intarray_create(10);
var_dump(intarray_check($a));
intarray_insert($a, 5, 10, true);
var_dump(intarray_check($a));
intarray_insert($a, 7, 10, true);
var_dump(intarray_check($a));
intarray_set($a, 9, 1);
var_dump(intarray_check($a));
echo "With index:\n";
var_dump(intarray_check($a, 0));
var_dump(intarray_check($a, 10));
var_dump(intarray_check($a, 11));
var_dump(intarray_check($a, 12));
var_dump(intarray_check($a, 13));

echo "Invalid types:\n";
var_dump(intarray_check("  "));
var_dump(intarray_check());
var_dump(intarray_check(true));
var_dump(intarray_check(false));
var_dump(intarray_check(null));
var_dump(intarray_check(1));
var_dump(intarray_check(0));
var_dump(intarray_check((object)array(12, 12, 434)));
var_dump(intarray_check(array()));
var_dump(intarray_check(array(1,2,3)));
var_dump(intarray_check(0.1));
var_dump(intarray_check(0.0));

?>
--EXPECTF--
Normal intarray:
bool(true)
Empty intarray:
bool(true)
bool(true)
bool(true)
Empty string:
bool(true)
Check after set and insert:
bool(true)
bool(true)
bool(true)
bool(true)
With index:
bool(true)
bool(true)
bool(true)
bool(false)
bool(false)
Invalid types:
bool(false)

Warning: intarray_check() expects at least 1 parameter, 0 given in %s on line %d
bool(false)
bool(false)
bool(false)
bool(false)
bool(false)
bool(false)
bool(false)
bool(false)
bool(false)
bool(false)
bool(false)
