package main

import (
	"context"
	"fmt"
	"math/rand"
	"runtime"
	"sync"
	"time"
)

func runFuncName() string {
	pc := make([]uintptr, 1)
	runtime.Callers(2, pc)
	f := runtime.FuncForPC(pc[0])
	return "\n" + f.Name() + " :"
}

func download(index int) int {
	d := rand.Intn(10)
	fmt.Println("index", index, "will take", d, "seconds")
	time.Sleep(time.Duration(d) * time.Second)
	return index
}

func chan_usage() {
	fmt.Println(runFuncName())

	ch := make(chan string)
	go func() {
		fmt.Println("other")
		ch <- "ok"
	}()
	fmt.Println("main")
	fmt.Println("recv :", <-ch)
}

func waitgroup_usage() {
	fmt.Println(runFuncName())

	chs := make([]chan int, 3)
	var wg sync.WaitGroup
	wg.Add(len(chs))
	defer wg.Wait()
	for i := range chs {
		chs[i] = make(chan int)
		go func(index int) {
			defer wg.Done()
			chs[index] <- download(index)
		}(i)
	}

	for cnt := 0; cnt != len(chs); {
		select {
		case index := <-chs[0]:
			fmt.Println("download", index, "finish.")
			cnt++
		case index := <-chs[1]:
			fmt.Println("download", index, "finish.")
			cnt++
		case index := <-chs[2]:
			fmt.Println("download", index, "finish.")
			cnt++
		}
	}
}

func select_usage() {
	fmt.Println(runFuncName())

	var wg sync.WaitGroup
	wg.Add(1)
	defer wg.Wait()

	stop_ch := make(chan bool)
	go func() {
		defer wg.Done()

		fmt.Println("coroutine start.")
		for {
			select {
			case <-stop_ch:
				fmt.Println("stop.")
				return
			default:
				fmt.Println("running.")
			}
			time.Sleep(time.Second)
		}
	}()
	time.Sleep(5 * time.Second)
	stop_ch <- true
	fmt.Println("main stop.")
}

func context_usage() {
	fmt.Println(runFuncName())

	// simple Context
	{
		var wg sync.WaitGroup
		wg.Add(1)
		defer wg.Wait()
		ctx, stop := context.WithCancel(context.Background())

		go func() {
			defer wg.Done()

			fmt.Println("coroutine start.")
			for {
				select {
				case <-ctx.Done():
					fmt.Println("stop.")
					return
				default:
					fmt.Println("running.")
				}
				time.Sleep(time.Second)
			}
		}()
		time.Sleep(5 * time.Second)
		stop()
		fmt.Println("main stop.")
	}

}

func concurrency_usage() {
	fmt.Println(runFuncName())

	// pipeline
	// ------
	f0 := func(n int) <-chan string {
		ret := make(chan string)
		go func() {
			defer close(ret)
			for i := 0; i < n; i++ {
				ret <- fmt.Sprint(i)
			}
		}()
		return ret
	}
	fn := func(in <-chan string, tag string) <-chan string {
		ret := make(chan string)
		go func() {
			defer close(ret)
			for v := range in {
				ret <- tag + "(" + v + ")"
			}
		}()
		return ret
	}

	{
		cc := f0(10)
		for i := 'a'; i <= 'g'; i++ {
			si := fmt.Sprintf("%c", i)
			cc = fn(cc, si)
		}
		for c := range cc {
			fmt.Println(c)
		}
	}

	// ---<>---
	merge := func(ins ...<-chan string) <-chan string {
		ret := make(chan string)
		var wg sync.WaitGroup
		wg.Add(len(ins))
		for _, in := range ins {
			go func(in <-chan string) {
				defer wg.Done()
				for s := range in {
					ret <- s
				}
			}(in)
		}
		go func() {
			defer close(ret)
			wg.Wait()
		}()
		return ret
	}
	{
		c0 := f0(10 * 3)
		c1 := fn(c0, "a")
		c2_1 := fn(c1, "b")
		c2_2 := fn(c1, "b")
		c2_3 := fn(c1, "b")
		c2 := merge(c2_1, c2_2, c2_3)
		c3 := fn(c2, "c")

		for c := range c3 {
			fmt.Println(c)
		}
	}

	// ===>---
}

func main() {
	rand.Seed(time.Now().UnixNano())

	concurrency_usage()

	chan_usage()

	// WaitGroup + chan
	waitgroup_usage()

	// sync's Mutex, RWMutex, Cond is like to cpp

	// select + chan to stop coroutine
	select_usage()

	context_usage()

}
