--TEST--
intarray_shuffle
--SKIPIF--
<?php if (!extension_loaded("intarray")) print "skip"; ?>
--FILE--
<?php 
/* empty */
$invalid_1 = " ";
$invalid_2 = 1;

$empty = intarray_create_from_array(array());
$one = intarray_create_from_array(array(10));
$normal = intarray_create_from_array(array(1,2,3,4,5));

error_reporting(false);
$r = intarray_shuffle($invalid_1);
var_dump($r);

$r = intarray_shuffle($invalid_2);
var_dump($r);

$r = intarray_shuffle($empty);
echo intarray_to_json($r), "\n";

$r = intarray_shuffle($one);
echo intarray_to_json($r), "\n";

$r = intarray_shuffle($normal);
echo intarray_to_json($r), "\n";


--EXPECTF--
bool(false)
bool(false)
[]
[10]
[%d,%d,%d,%d,%d]
