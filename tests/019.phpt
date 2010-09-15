--TEST--
intarray_binarysearch_slot
--SKIPIF--
<?php if (!extension_loaded("intarray")) print "skip"; ?>
--FILE--
<?php 

$intarray = intarray_create_from_array(array(1, 2, 4, 8, 16));
intarray_dump($intarray);
echo "\n";

echo intarray_binarysearch_slot($intarray, -1), "\n";
echo intarray_binarysearch_slot($intarray, 0), "\n";
echo intarray_binarysearch_slot($intarray, 1), "\n";
echo intarray_binarysearch_slot($intarray, 2), "\n";
echo intarray_binarysearch_slot($intarray, 3), "\n";
echo intarray_binarysearch_slot($intarray, 4), "\n";
echo intarray_binarysearch_slot($intarray, 5), "\n";
echo intarray_binarysearch_slot($intarray, 8), "\n";
echo intarray_binarysearch_slot($intarray, 13), "\n";
echo intarray_binarysearch_slot($intarray, 16), "\n";
echo intarray_binarysearch_slot($intarray, 17), "\n";

echo "empty intarray\n";
error_reporting(0);
$intarray = '';
echo intarray_binarysearch_slot($intarray, -1), "\n";
echo intarray_binarysearch_slot($intarray, 0), "\n";
echo intarray_binarysearch_slot($intarray, 1), "\n";

echo "one intarray\n";
error_reporting(0);
$intarray = '';
$intarray = intarray_create_from_array(array(1));
echo intarray_binarysearch_slot($intarray, 0), "\n";
echo intarray_binarysearch_slot($intarray, 1), "\n";
echo intarray_binarysearch_slot($intarray, 2), "\n";

$intarray = '';
for ($i = 1; $i < 2 * 4; $i++) {
	$intarray .= "\x01";
	$slot_left = intarray_binarysearch_slot($intarray, 0);
	$slot_find = intarray_binarysearch_slot($intarray,  0x0000ffff);
	$slot_right = intarray_binarysearch_slot($intarray, 0x7fffffff);
	if ($i % 4 != 0) {
		if ($slot_left !== false || $slot_right !== false || $slot_find !== false) {
			echo "strange, everything should be false\n";
			var_dump($slot_left);
			var_dump($slot_find);
			var_dump($slot_right);
		}
	} else {
		if ($slot_left !== 0 || $slot_find !== 0 || $slot_right !== 1) {
			echo "strange, should be 0, 0, 1\n";
			var_dump($slot_left);
			var_dump($slot_find);
			var_dump($slot_right);
		}
	}
}

--EXPECT--
{ 1, 2, 4, 8, 16 }
0
0
0
1
2
2
3
3
4
4
5
empty intarray
0
0
0
one intarray
0
0
1
