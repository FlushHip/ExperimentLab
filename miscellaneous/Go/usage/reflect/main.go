package main

import (
	"encoding/json"
	"fmt"
	"reflect"
	"runtime"

	"gopkg.in/yaml.v2"
)

func runFuncName() string {
	pc := make([]uintptr, 1)
	runtime.Callers(2, pc)
	f := runtime.FuncForPC(pc[0])
	return "\n" + f.Name() + " :"
}

type person struct {
	Name string `json:"name_json" yaml:"name_yaml"`
	Age  int    `json:"age_json" yaml:"age_yaml"`
}

func (p person) String() string {
	return fmt.Sprintf("Name: %s, Age: %d", p.Name, p.Age)
}

func (p person) Print(prefix string) {
	fmt.Println(prefix, p)
}

func main() {
	fmt.Println(runFuncName())
	p := person{Name: "FlushHip", Age: 27}
	fmt.Println(p)
	ppv := reflect.ValueOf(&p)
	ppv.Elem().Field(0).SetString("lisi")
	fmt.Println(p)

	pt := reflect.TypeOf(p)
	for i := 0; i < pt.NumField(); i++ {
		fmt.Println(pt.Field(i).Name)
	}
	for i := 0; i < pt.NumMethod(); i++ {
		fmt.Println(pt.Method(i).Name)
	}

	{
		// struct to json
		str, err := json.Marshal(p)
		if err != nil {
			fmt.Println(err)
		}
		fmt.Println(string(str))

		// json to struct
		err = json.Unmarshal(str, &p)
		if err != nil {
			fmt.Println(err)
		}
		fmt.Println(p)
	}

	{
		// struct to yaml
		str, err := yaml.Marshal(p)
		if err != nil {
			fmt.Println(err)
		}
		fmt.Println(string(str))

		// yaml to struct
		err = yaml.Unmarshal(str, &p)
		if err != nil {
			fmt.Println(err)
		}
		fmt.Println(p)
	}

	// call method by reflect
	pv := reflect.ValueOf(p)
	args := []reflect.Value{reflect.ValueOf("FlushHip")}
	pv.MethodByName("Print").Call(args)

}
