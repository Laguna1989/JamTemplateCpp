# Contribution guidelines

It's great that you want to contribute to the JamTemplate!
Here are some guidelines to make sure we keep this a stable project.

### 1. Check if there is an issue for the PR
In short this means that I must be aware of an issue and accept it. 
If the issue is about a potential new feature, it's important that you
describe in detail why this feature is needed.

Also: If you are interested in fixing or developing on an existing issue, 
please comment in the issue before you start working on it. This is mainly to 
prevent that two people work on the same feature.

### 2. Every issue must have a unit test proving that it works
If you have either fixed a bug or created a new feature, you must prove that everything works
as intended by creating a test to prove that the logic works. Additionally, 
you must make sure that all the other tests still works after your change.
This can be done by building and executing the `jt_test`, `jt_demos`, 
`jt_performance` (with `-DJT_ENABLE_PERFORMANCETESTS=ON`) and `JamTemplate` targets. 
This will also be checked by automatic github actions once you create a PR, but checking 
it locally on your machine will save some time.

### 3. Make sure the demos still work and are updated appropriately
The examples in `jt_demos` use the code from the JamTemplate to showcase some of the features. 
If you work on a feature that is already showcased, think about how to extend the demos. 
If there are no demos yet, think about creating some. This can of course be further discussed in the issue/PR.

### 4. Update the Doxygen documentation
This is something I do not strictly require for accepting a pull request, but it's nice
to keep in mind. You will need to have Doxygen installed on your local environment
to make this work, but you can do this by simply going into the `doc/doxygen` folder with 
your console application of choice and run the `doxygen` command.
