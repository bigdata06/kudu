// Copyright (c) 2014, Cloudera, inc.
package kudu.rpc;

public class AlterTableResponse extends KuduRpcResponse {

  /**
   * @param ellapsedMillis Time in milliseconds since RPC creation to now.
   */
  AlterTableResponse(long ellapsedMillis) {
    super(ellapsedMillis);
  }
}