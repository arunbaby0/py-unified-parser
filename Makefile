# Set some sensible defaults for the Makefile
SHELL := bash
.SHELLFLAGS := -eu -o pipefail -c
.ONESHELL:
.DELETE_ON_ERROR:
MAKEFLAGS += --warn-undefined-variables
MAKEFLAGS += --no-builtin-rules

# Use > to mark recipes instead of tabs
ifeq ($(origin .RECIPEPREFIX), undefined)
	$(error This version of make does not support .RECIPEPREFIX. Please use GNU Make v4.0 or later)
endif

.RECIPEPREFIX = >

# HELP
# This will output the help for each task
# thanks to https://marmelab.com/blog/2016/02/29/auto-documented-makefile.html
.PHONY: help check clean

help: ## This help.
> @awk 'BEGIN {FS = ":.*?## "} /^[a-zA-Z_-]+:.*?## / {printf "\033[36m%-30s\033[0m %s\n", $$1, $$2}' $(MAKEFILE_LIST)

.DEFAULT_GOAL := help

SRC          ?= src
TEST         ?= tests
BRANCH       := $(shell git branch --show-current)
PY_SRC       := $(shell find $(SRC) -type f \( ! -iname "version.py" \))
PY_TEST      := $(shell find $(TEST) -type f)
PY_MODULE    := $(shell ls $(SRC))
VERSION_FILE := $(shell find $(SRC) -type f -name "final-release.version")

clean: ## Remove markers to make sure all targets are executed
> find . -name '*.pyc' -exec rm -f {} +
> find . -name '*.pyo' -exec rm -f {} +
> find . -name '*~' -exec rm -f  {} +
> rm -rf build/
> rm -rf .mypy_cache/
> rm -rf out/

out/.lint: $(PY_SRC)
> poetry run flake8
> mkdir -p $(@D)
> touch $@

out/.format: $(PY_SRC) $(PY_TEST)
> poetry run black $(SRC) $(TEST)
> poetry run isort --profile=black $(SRC) $(TEST)
> mkdir -p $(@D)
> touch $@

out/.mypy: $(PY_SRC)
> poetry run mypy --namespace-packages $(SRC)
> mkdir -p $(@D)
> touch $@

check: out/.format out/.lint out/.mypy ## Check source files

out/.test: $(PY_SRC) $(PY_TEST)
> poetry run pytest -s
> mkdir -p $(@D)
> touch $@

test: out/.test ## Run tests

# BUMP can be manualy specified. If it has not been specified, calculate BUMP based on type of branch
ifndef BUMP
  ifneq (,$(findstring feature,$(BRANCH)))
    BUMP := minor
  else
    BUMP := patch
  endif
endif

# Define BUMP_TAG appropriately based on BUMP
ifeq ($(BUMP),patch)
  BUMP_TAG := maintenance
else
  BUMP_TAG := $(BUMP)
endif


out/.update-poetry-version: $(PY_SRC) $(PY_TEST) pyproject.toml poetry.lock Makefile
ifeq ($(shell cat $(VERSION_FILE)),$(shell poetry version --short))
  ifeq ($(BRANCH), master)
> @echo A new version should not be started in the master branch. Use a feature or bugfix branch instead.
> false
  else
> export MSG=`poetry version pre$(BUMP)`
> jq '(.release_type) = "$(BUMP_TAG)"' version.json > version.json.new
> mv version.json.new version.json
> git add version.json
  endif
else
  ifneq ($(BRANCH), master)
> poetry version prerelease
> git add pyproject.toml
  else
> @echo Version bump should be handled by CI
> @echo Not making any changes
  endif
endif
> mkdir -p $(@D)
> touch $@


out/.version: pyproject.toml out/.update-poetry-version
> mkdir -p $(@D)
> touch $@

version: out/.version ## Bump version

out/.build: out/.version out/.test  $(PY_SRC) $(PY_TEST) pyproject.toml poetry.lock
> poetry build
> mkdir -p $(@D)
> touch $@

build: out/.build ## Build python package whl


out/.release: out/.build
> export VERSION=$(shell poetry version --short)
ifeq ($(BRANCH), master)
> @echo release from master must be done through CI
> false
else
> @echo Released version $$VERSION
endif

release: out/.release ## Release python package