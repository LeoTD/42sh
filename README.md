# 42sh
> A minimal shell

An interactive shell built for a school project. It does what you would
expect a shell to do and can be used intuitively by anyone familiar with `sh`,
`bash`, etc.

## Build instructions

```shell
git clone $thisrepo
cd 42sh
make
```

## Features

#### The shell builtins `cd`, `env` `echo`, `setenv`, and `unsetenv` (see [Builtins](#builtins))

#### Path management
	$> which grep
	/usr/bin/grep
	$> unsetenv PATH
	$> which grep || echo notfound
	notfound
	$> setenv PATH /usr/bin:/bin
	$> which grep
	/usr/bin/grep

#### Output redirection with `>` and `>>`
	$> echo a > afile
	$> cat afile
	a
	$> echo a2 >> afile
	$> cat afile
	a
	a2

#### Output redirection to file descriptor
	$> git errorsplease 2>oops
	$> cat oops
	git: 'errorsplease' is not a git command. See 'git --help'.

#### Input redirection with `<`
	$> wc -c < afile
	5

#### The pipeline operator `|`
	$> echo 5 + 5 | bc
	10

#### The list separators `&&`, `||` and `;`
	$> false && echo foo || echo bar
	bar
	$> true || echo foo && echo bar
	bar
	false; false; echo bar
	ok

## Builtins

### setenv
	$> setenv FOO bar # add FOO=bar to the environment, or replace existing value of FOO
	$> setenv # print every current environment variable, format "KEY=val\n"

### unsetenv
	$> unsetenv FOO # remove FOO from the environment, if present

### env
	$> env # identical to setenv with no arguments
	$> env CLICOLOR=1 ls # set an environment variable for one invocation of utility

## Credits

### Authors

* [Joshua Gelbard](https://github.com/joshgelbard)
* [Curtis Krommenhoek](https://github.com/cpk42)
* [Ezekiel Liu](https://github.com/eliu42)
* [Gerardo Malpartida](https://github.com/regien)
* [Liam Prior](https://github.com/LiamPrior)
* [Leo Tanenbaum-Diaz](https://github.com/LeoTD)

### Thanks to
* [s](https://github.com/rain-1/s) -- A great example of how to structure an interpreter


## License

MIT License

Copyright (c) 2019 Joshua Gelbard, Curtis Krommenhoek, Ezekiel Liu, Gerardo Malpartida, Liam Prior, and Leo Tanenbaum-Diaz

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
