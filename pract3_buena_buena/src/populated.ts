import { Db, MongoClient } from "mongodb";

export const getDocuments = async (): Promise<Db> => {
  const dbName: string = "Coworking";
  const collection: string = "Documentos";
/*
  const usr = "avalero";
  const pwd = "******";
  const mongouri: string = `mongodb+srv://${usr}:${pwd}@cluster-nebrija.gcxdd.gcp.mongodb.net/${dbName}?retryWrites=true&w=majority`;
*/
const mongouri:string="mongodb+srv://mgh99:mariagh99@cluster0.r1qlh.mongodb.net/Maria?retryWrites=true&w=majority";
  const client = new MongoClient(mongouri);

  try {
    await client.connect();
    console.info("MongoDB connected");
      return client.db(dbName);
  } catch (e) {
    throw e;
  }
};