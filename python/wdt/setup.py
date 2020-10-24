import setuptools

with open("README.md", "r") as fh:
    long_description = fh.read()

setuptools.setup(
    name="wdt",
    version="2.0.1",
    author="Alexandru Burcea",
    author_email="olcit@gmail.com",
    description="A set of functions to control Sequent Microsystems Watchdog for Raspberry board",
    license='MIT',
    url="https://github.com/SequentMicrosystems/wdt-rpi",
    packages=setuptools.find_packages(),
    classifiers=[
        "Programming Language :: Python :: 2/3",
        "License :: OSI Approved :: MIT License",
        "Operating System :: OS Independent",
    ],
)
