package main

import (
	"errors"
	"fmt"
	"runtime"
	"strconv"
	"strings"
)

func runFuncName() string {
	pc := make([]uintptr, 1)
	runtime.Callers(2, pc)
	f := runtime.FuncForPC(pc[0])
	return "\n" + f.Name() + " :"
}

func get_sum(a int, b int) (int, error) {
	if a < 0 || b < 0 {
		return 0, errors.New("element < 0 is invalid")
	}
	return a + b, nil
}

func get_sums(params ...int) (int, error) {
	ret := 0
	for _, v := range params {
		if v < 0 {
			return 0, errors.New("element < 0 is invalid")
		}
		ret += v
	}
	return ret, nil
}

func basic_usage() {
	fmt.Println(runFuncName())

	/*
		fmt.Println("flushhip")
		fmt.Println("yes")
	*/

	// int
	var a int = 1
	aa := 1
	const aaa = 1
	p_a := &a
	s_a := strconv.Itoa(a)
	fmt.Println(a, aa, aaa, p_a, s_a)

	// float
	var b float64 = 1.2
	bb := b
	fmt.Println(b, bb)

	// bool
	var f bool = false
	ff := f
	fmt.Println(f, ff)

	// string
	var s string = "flushhip"
	ss := s
	result := strings.Contains(s, "f")
	fmt.Println(s, ss, result)

	// if
	if a > 1 {
		fmt.Println("a greater than 1")
	} else {
		fmt.Println("a not greate than 1")
	}

	// for
	sum := 0
	for i := 0; i < 100; i += 2 {
		sum += i
	}
	fmt.Println(sum)

	// array
	arr := [3]string{"a", "b", "c"}
	fmt.Println(len(arr), cap(arr))
	for i, v := range arr {
		fmt.Println(i, ":", v)
	}
	arr2 := [3][3]int{
		{1, 2, 3},
		{4, 5, 6},
		{7, 8, 9},
	}
	fmt.Println(arr2)

	// slice
	vec := []string{"d", "e", "f"}
	fmt.Println(len(vec), cap(vec))
	vec_aux := vec[1:2]
	fmt.Println(len(vec_aux), cap(vec_aux))
	for i, v := range vec {
		fmt.Println(i, ":", v)
	}

	// map
	mp := make(map[string]int)
	mp["lisi"] = 6523
	mp["chenyang"] = 2580
	if value, has := mp["lisi"]; has {
		fmt.Println(value)
	}
}

func func_usage() {
	fmt.Println(runFuncName())
	// function
	{
		result, err := get_sum(1, -1)
		fmt.Println(result, err)
		result, err = get_sum(1, 2)
		fmt.Println(result, err)
	}
	{
		result, err := get_sums(1, 2, 3, 4, 5)
		fmt.Println(result, err)
	}

	// colsure
	fn := func() func() int {
		i := 0
		return func() int {
			i++
			return i
		}
	}
	fmt.Println(fn()())
	fmt.Println(fn()())
	fmt.Println(fn()())
	{
		fn := fn()
		fmt.Println(fn())
		fmt.Println(fn())
		fmt.Println(fn())
	}

}

type person struct {
	name string
	age  uint
}

func (p person) String() string {
	return fmt.Sprintf("name: %s, age: %d", p.name, p.age)
}

func printString(s fmt.Stringer) {
	fmt.Println(s.String())
}

func struct_interface_usage() {
	fmt.Println(runFuncName())

	p_a := person{"lisi", 26}
	fmt.Println(p_a)
	printString(p_a)
	p_b := person{age: 27, name: "chenyang"}
	fmt.Println(p_b)
	printString(p_b)
}

func main() {

	basic_usage()
	func_usage()
	struct_interface_usage()
}
