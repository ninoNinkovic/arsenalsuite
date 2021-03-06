CREATE OR REPLACE FUNCTION job_delete()
  RETURNS trigger AS
$BODY$
DECLARE
    stat RECORD;
BEGIN
    DELETE FROM jobassignment WHERE fkeyjob = OLD.keyjob;
    DELETE FROM jobtask     WHERE fkeyjob = OLD.keyjob;
    DELETE FROM joberror    WHERE fkeyjob = OLD.keyjob;
    DELETE FROM jobhistory  WHERE fkeyjob = OLD.keyjob;
    DELETE FROM jobstatus   WHERE fkeyjob = OLD.keyjob;
    DELETE FROM jobservice  WHERE fkeyjob = OLD.keyjob;
    DELETE FROM jobdep      WHERE fkeyjob = OLD.keyjob;
    DELETE FROM joboutput   WHERE fkeyjob = OLD.keyjob;

    RETURN OLD;
END;
$BODY$
  LANGUAGE plpgsql VOLATILE
  COST 100;

CREATE TRIGGER Job_Delete AFTER DELETE ON job FOR EACH ROW EXECUTE PROCEDURE job_delete();
CREATE TRIGGER JobBatch_Delete AFTER DELETE ON jobbatch FOR EACH ROW EXECUTE PROCEDURE job_delete();
CREATE TRIGGER JobMax7_Delete AFTER DELETE ON jobmax7 FOR EACH ROW EXECUTE PROCEDURE job_delete();
CREATE TRIGGER JobMax8_Delete AFTER DELETE ON jobmax8 FOR EACH ROW EXECUTE PROCEDURE job_delete();
CREATE TRIGGER JobMax9_Delete AFTER DELETE ON jobmax9 FOR EACH ROW EXECUTE PROCEDURE job_delete();
CREATE TRIGGER JobMax10_Delete AFTER DELETE ON jobmax10 FOR EACH ROW EXECUTE PROCEDURE job_delete();
CREATE TRIGGER JobMax2009_Delete AFTER DELETE ON jobmax2009 FOR EACH ROW EXECUTE PROCEDURE job_delete();
CREATE TRIGGER JobMaxScript_Delete AFTER DELETE ON jobmaxscript FOR EACH ROW EXECUTE PROCEDURE job_delete();
CREATE TRIGGER JobXSI_Delete AFTER DELETE ON jobxsi FOR EACH ROW EXECUTE PROCEDURE job_delete();
CREATE TRIGGER JobXSIScript_Delete AFTER DELETE ON jobxsiscript FOR EACH ROW EXECUTE PROCEDURE job_delete();
CREATE TRIGGER JobCinema4d_Delete AFTER DELETE ON JobCinema4d FOR EACH ROW EXECUTE PROCEDURE job_delete();
CREATE TRIGGER JobAfterEffects_Delete AFTER DELETE ON JobAfterEffects FOR EACH ROW EXECUTE PROCEDURE job_delete();
CREATE TRIGGER JobAfterEffects7_Delete AFTER DELETE ON JobAfterEffects7 FOR EACH ROW EXECUTE PROCEDURE job_delete();
CREATE TRIGGER JobAfterEffects8_Delete AFTER DELETE ON JobAfterEffects8 FOR EACH ROW EXECUTE PROCEDURE job_delete();
CREATE TRIGGER JobMaya7_Delete AFTER DELETE ON JobMaya7 FOR EACH ROW EXECUTE PROCEDURE job_delete();
CREATE TRIGGER JobMaya85_Delete AFTER DELETE ON JobMaya85 FOR EACH ROW EXECUTE PROCEDURE job_delete();
CREATE TRIGGER JobMaya2008_Delete AFTER DELETE ON JobMaya2008 FOR EACH ROW EXECUTE PROCEDURE job_delete();
CREATE TRIGGER JobMaya2009_Delete AFTER DELETE ON JobMaya2009 FOR EACH ROW EXECUTE PROCEDURE job_delete();
CREATE TRIGGER JobMaya2011_Delete AFTER DELETE ON JobMaya2011 FOR EACH ROW EXECUTE PROCEDURE job_delete();
CREATE TRIGGER JobMentalRay85_Delete AFTER DELETE ON JobMentalRay85 FOR EACH ROW EXECUTE PROCEDURE job_delete();
CREATE TRIGGER JobMentalRay2009_Delete AFTER DELETE ON JobMentalRay2009 FOR EACH ROW EXECUTE PROCEDURE job_delete();
CREATE TRIGGER JobMentalRay2011_Delete AFTER DELETE ON JobMentalRay2011 FOR EACH ROW EXECUTE PROCEDURE job_delete();
CREATE TRIGGER JobShake_Delete AFTER DELETE ON JobShake FOR EACH ROW EXECUTE PROCEDURE job_delete();
CREATE TRIGGER JobSync_Delete AFTER DELETE ON JobSync FOR EACH ROW EXECUTE PROCEDURE job_delete();
CREATE TRIGGER JobFusion_Delete AFTER DELETE ON JobFusion FOR EACH ROW EXECUTE PROCEDURE job_delete();
CREATE TRIGGER JobFusionVideoMaker_Delete AFTER DELETE ON JobFusionVideoMaker FOR EACH ROW EXECUTE PROCEDURE job_delete();
CREATE TRIGGER JobNuke51_Delete AFTER DELETE ON JobNuke51 FOR EACH ROW EXECUTE PROCEDURE job_delete();
CREATE TRIGGER JobNuke52_Delete AFTER DELETE ON JobNuke52 FOR EACH ROW EXECUTE PROCEDURE job_delete();
CREATE TRIGGER JobMantra100_Delete AFTER DELETE ON JobMantra100 FOR EACH ROW EXECUTE PROCEDURE job_delete();
CREATE TRIGGER Job3Delight_Delete AFTER DELETE ON Job3Delight FOR EACH ROW EXECUTE PROCEDURE job_delete();
CREATE TRIGGER JobRealFlow_Delete AFTER DELETE ON JobRealFlow FOR EACH ROW EXECUTE PROCEDURE job_delete();
CREATE TRIGGER JobHoudiniSim10_Delete AFTER DELETE ON JobHoudiniSim10 FOR EACH ROW EXECUTE PROCEDURE job_delete();
CREATE TRIGGER JobNaiad_Delete AFTER DELETE ON JobNaiad FOR EACH ROW EXECUTE PROCEDURE job_delete();

