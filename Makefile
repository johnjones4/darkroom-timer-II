.PHONY: data

clean:
	rm -rf data || true
	
data: clean
	cp -R data_dev data
	cd data && gzip index.html
	cd data && gzip data.json

devserver:
	cd data_dev && python3 -m http.server 4000