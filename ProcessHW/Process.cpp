#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include "Process.hpp"

Process::Process(const std::vector<char*>& args, bool verbose) :
    verbose(verbose),
    m_name(args[0]),
    m_pid((pid_t)NULL),
    m_writepipe {-1,-1},
    m_readpipe {-1,-1},
    m_pwrite((FILE*)NULL),
    m_pread((FILE*)NULL)
{
    if(args[0] == NULL){
	perror("No input");
	throw std::string("No input");
    } else{
	m_name = args[0];
    }

    if(pipe(m_writepipe) < 0 || pipe(m_readpipe) < 0){
	perror("pipe");
	throw std::string("Pipe");
    }

    if ((m_pid = fork()) < 0)
    {
	perror("Process fork");
	throw std::string("Process fork");
    } else if ( m_pid == 0 ) {
	/* child process */

	close( PARENT_WRITE );
	close( PARENT_READ );
	dup2( CHILD_WRITE, 1);
	close( CHILD_WRITE );
	dup2( CHILD_READ, 0);
	close(CHILD_READ);
	execvp(args[0], const_cast<char**>(&args[0]));
	perror("Process execvp");
	throw std::string("Process execvp");
    } else {
	/* parent process */
	if (verbose)
        std::cerr << "Process " << m_name << ": forked PID " << m_pid << std::endl;
	close(CHILD_READ);
	close(CHILD_WRITE);
	m_pread = fdopen(PARENT_READ, "r");
	m_pwrite = fdopen( PARENT_WRITE, "w");
    }
};

Process::~Process()
{
    if (verbose)
	std::cerr << "Process " << m_name << ": Entering ~Process()" << std::endl;

    fclose(m_pwrite);
    waitpid(m_pid, &rtval, 0);
    fclose(m_pread);
    if (pid < 0)
	perror("~Process waitpid");

    if (verbose)
	std::cerr << "Process " << m_name << ": Leaving ~Process()" << std::endl;
};

void Process::write(const std::string& line)
{
    fputs(line.c_str(), m_pwrite);
    fflush(m_pwrite);
}

std::string Process::read()
{
    std::string line;
    char* mystring = NULL;
    size_t num_bytes;

    getline(&mystring. &num_bytes, m_pread);
    line = mystring;
    return line;
}
