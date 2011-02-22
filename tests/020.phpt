--TEST--
intarray_binarysearch_slot
--SKIPIF--
<?php if (!extension_loaded("intarray")) print "skip"; ?>
--FILE--
<?php 

$intarray = intarray_create_from_array(array(2, 3, 4, 5, 10, 11, 12));
intarray_dump($intarray);
echo "\n";
// { 2, 3, 4, 5, 10, 11, 12 }
intarray_dump(intarray_subset($intarray, 2, 12)); echo "\n";
// { 2, 3, 4, 5, 10, 11, 12 }
intarray_dump(intarray_subset($intarray, 1, 13)); echo "\n";
// { 2, 3, 4, 5, 10, 11, 12 }
intarray_dump(intarray_subset($intarray, -100, 100)); echo "\n";
// { 2, 3, 4, 5, 10, 11, 12 }
intarray_dump(intarray_subset($intarray, 0, 1)); echo "\n";
// { }
intarray_dump(intarray_subset($intarray, 0, 2)); echo "\n";
// { 2 }
intarray_dump(intarray_subset($intarray, 2, 2)); echo "\n";
// { 2 }
intarray_dump(intarray_subset($intarray, 0, 3)); echo "\n";
// { 2, 3 }
intarray_dump(intarray_subset($intarray, 3, 5)); echo "\n";
// { 3, 4, 5 }
intarray_dump(intarray_subset($intarray, 3, 6)); echo "\n";
// { 3, 4, 5 }
intarray_dump(intarray_subset($intarray, 5, 6)); echo "\n";
// { 5 }
intarray_dump(intarray_subset($intarray, 6, 7)); echo "\n";
// { }
intarray_dump(intarray_subset($intarray, 8, 10)); echo "\n";
// { 10 }
intarray_dump(intarray_subset($intarray, 10, 12)); echo "\n";
// { 10, 11, 12 }
intarray_dump(intarray_subset($intarray, 10, 13)); echo "\n";
// { 10, 11, 12 }
intarray_dump(intarray_subset($intarray, 12, 13)); echo "\n";
// { 12 }
intarray_dump(intarray_subset($intarray, 13, 15)); echo "\n";
// { }

echo "empty intarray\n";
error_reporting(0);
$intarray = '';

intarray_dump(intarray_subset($intarray, 13, 15)); echo "\n";
// { }

--EXPECT--
{ 2, 3, 4, 5, 10, 11, 12 }
{ 2, 3, 4, 5, 10, 11, 12 }
{ 2, 3, 4, 5, 10, 11, 12 }
{ 2, 3, 4, 5, 10, 11, 12 }
{ }
{ 2 }
{ 2 }
{ 2, 3 }
{ 3, 4, 5 }
{ 3, 4, 5 }
{ 5 }
{ }
{ 10 }
{ 10, 11, 12 }
{ 10, 11, 12 }
{ 12 }
{ }
empty intarray
{ }
