package main

import "net/http"
import "log"

func main() {
	http.Handle("/", http.FileServer(http.Dir(".")))
	log.Fatal(http.ListenAndServe(":3333", nil))
}
