run:
		go run webserver.go

dist:
		mkdir dist
		cp index-dist.html dist/index.html
		cp favicon.png dist/
		jspm bundle-sfx lib/app.js dist/bundle.js --minify

clean:
		rm -rf dist
