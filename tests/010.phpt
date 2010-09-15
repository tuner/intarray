--TEST--
intarray_search intarray_binarysearch
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

$intarray = intarray_create_from_array(array(1, 2, 4, 8, 16));
intarray_dump($intarray);
echo "\n";

echo intarray_search($intarray, 2), "\n";
echo intarray_search($intarray, 3), "\n";

echo intarray_binarysearch($intarray, 8), "\n";
echo intarray_binarysearch($intarray, 7), "\n";

$intarray = "";

echo intarray_search($intarray, 2), "\n";
echo intarray_binarysearch($intarray, 2), "\n";

$intarray = intarray_create_from_array(array(1, 2, 4, 8, 16));

echo intarray_search($intarray, 4, 2), "\n";
echo intarray_search($intarray, 4, -3), "\n";
echo intarray_search($intarray, 4, 3), "\n";
echo intarray_search($intarray, 4, -2), "\n";
echo intarray_search($intarray, 4, -1000), "\n";
echo intarray_search($intarray, 4, 1000), "\n";

$intarray = intarray_create_from_array(array());
intarray_dump($intarray);
echo "\n";
echo intarray_binarysearch($intarray, 10), "\n";
echo intarray_search($intarray, 10), "\n";
echo intarray_search($intarray, 10, -1), "\n";
echo intarray_search($intarray, 10, 0), "\n";
echo intarray_search($intarray, 10, 1), "\n";
?>
--EXPECT--
{ 1, 2, 4, 8, 16 }
1
-1
3
-1
-1
-1
2
2
-1
-1
-1
-1
{ }
-1
-1
-1
-1
-1
