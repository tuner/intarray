--TEST--
intarray_difference
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
intarray_dump($a);
echo "\n";

intarray_dump(intarray_difference($a, $a));
echo "\n";

$b = intarray_create_from_array(array(1, 2, 3));
intarray_dump($b);
echo "\n";

intarray_dump(intarray_difference($a, $b));
echo "\n";

intarray_dump(intarray_difference($b, $a));
echo "\n";

$c = intarray_create_from_array(array(4, 5, 6, 7));
intarray_dump($c);
echo "\n";

intarray_dump(intarray_difference($a, $c));
echo "\n";

intarray_dump(intarray_difference($c, $a));
echo "\n";

intarray_dump(intarray_difference($b, $c));
echo "\n";

intarray_dump(intarray_difference($c, $b));
echo "\n";

echo "empty sets\n";
intarray_dump(intarray_difference($a, ""));
echo "\n";

intarray_dump(intarray_difference("", $a));
echo "\n";

$c = intarray_difference($a, "");
intarray_set($c, 0, 5);
intarray_dump($a);
echo "\n";
intarray_dump($c);
echo "\n";

$a = intarray_create(0);
$b = intarray_create(0);
intarray_dump(intarray_difference($a, $b));
echo "\n";

?>
--EXPECT--
{ 1, 2, 3, 4, 5 }
{ }
{ 1, 2, 3 }
{ 4, 5 }
{ }
{ 4, 5, 6, 7 }
{ 1, 2, 3 }
{ 6, 7 }
{ 1, 2, 3 }
{ 4, 5, 6, 7 }
empty sets
{ 1, 2, 3, 4, 5 }
{ }
{ 1, 2, 3, 4, 5 }
{ 5, 2, 3, 4, 5 }
{ }
