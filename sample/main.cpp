#include <pistache/endpoint.h>
#include <cassandra.h>


CassCluster* cluster;
CassSession* session;


using namespace Pistache;

struct HelloHandler : public Http::Handler {
  HTTP_PROTOTYPE(HelloHandler)
  void onRequest(const Http::Request&, Http::ResponseWriter writer) override {
    
	
	
    CassStatement* statement = cass_statement_new("select name from unittest_f3249f19_5d71_4a19_bd6a_87cae7daa860.foos", 0);
	
    CassFuture* result_future = cass_session_execute(session, statement);

    if(cass_future_error_code(result_future) == CASS_OK) {
      /* Retrieve result set and iterate over the rows */
      const CassResult* result = cass_future_get_result(result_future);
      CassIterator* rows = cass_iterator_from_result(result);
	std::string r;
      while(cass_iterator_next(rows)) {
        const CassRow* row = cass_iterator_get_row(rows);
        const CassValue* value = cass_row_get_column_by_name(row, "name");

        const char* keyspace;
        size_t keyspace_length;
        cass_value_get_string(value, &keyspace, &keyspace_length);
        char b[200];
		sprintf(b, "Name: '%.*s'\n", (int)keyspace_length, keyspace);
		r += b;
      }

      cass_result_free(result);
      cass_iterator_free(rows);	
	  
	 writer.send(Http::Code::Ok, r);
	}
	
  }
};

int main() {
	
	CassFuture* connect_future = NULL;
	cluster = cass_cluster_new();
	session = cass_session_new();

	cass_cluster_set_contact_points(cluster, "192.168.1.155");

    connect_future = cass_session_connect(session, cluster);

	if (cass_future_error_code(connect_future) != CASS_OK) {
		printf("Could not connect to cluster\n");
		exit(1);
	}
	
	
	
  Http::listenAndServe<HelloHandler>(Pistache::Address("*:9082"));
}

// unittest_f3249f19_5d71_4a19_bd6a_87cae7daa860
