import setuptools

setuptools.setup(
    name='SMwdt',
    packages=setuptools.find_packages(),
    version='1.0.2',
    license='MIT',
    description='Library to control Sequent Microsystems wdt Card',
    author='Sequent Microsystems',
    author_email='olcitu@gmail.com',
    url='https://sequentmicrosystems.com',
    install_requires=[
        "smbus2",
        ],
    #keywords=['industrial', 'raspberry', 'power', '4-20mA', '0-10V', 'optoisolated'],
    classifiers=[
        'Development Status :: 4 - Beta',
        # Chose either "3 - Alpha", "4 - Beta" or "5 - Production/Stable" as the current state of your package
        'Intended Audience :: Developers',
        'Topic :: Software Development :: Build Tools',
        'License :: OSI Approved :: MIT License',
        'Programming Language :: Python :: 2.7',
        'Programming Language :: Python :: 3',
        'Programming Language :: Python :: 3.4',
        'Programming Language :: Python :: 3.5',
        'Programming Language :: Python :: 3.6',
        'Programming Language :: Python :: 3.7',
    ],
)
