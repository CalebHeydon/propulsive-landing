import sys

package = sys.argv[1]
packagesite_yaml = open("tmp/packagesite.yaml")
lines = packagesite_yaml.readlines()

for line in lines:
	if f"\"name\":\"{package}\"" in line:
		i = line.find("\"version\":\"") + len("\"version\":\"")
		substring = line[i:]
		i = substring.find("\"")
		version = substring[:i]
		print(f"{package}-{version}.pkg")
		exit()
