--TEST--
intarray_to_json
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

$a = intarray_create_from_array(array(1, 2, 3, 4, 5));
echo intarray_to_json($a);
echo "\n";

$a = intarray_create(0);
echo intarray_to_json($a);
echo "\n";

intarray_insert($a, 0, 10, true);
intarray_insert($a, 1, 10, true);
echo intarray_to_json($a), "\n";

$a = intarray_create(10);
intarray_insert($a, 5, 10, true);
intarray_insert($a, 7, 10, true);
intarray_set($a, 9, 1);
echo intarray_to_json($a), "\n";

var_dump(intarray_to_json(""));
var_dump(intarray_to_json(null));
var_dump(intarray_to_json(true));
?>
--EXPECTF--
[1,2,3,4,5]
[]
[10,10]
[0,0,0,0,0,10,0,10,0,1,0,0]
string(2) "[]"

Warning: Doesn't seem to be an intarray, not a binarystring! in %s on line %d
bool(false)

Warning: Doesn't seem to be an intarray, not a binarystring! in %s on line %d
bool(false)
